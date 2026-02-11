cpu_write_( hes_addr_t addr, int data )
{
	if ( unsigned (addr - apu.start_addr) <= apu.end_addr - apu.start_addr )
	{
		GME_APU_HOOK( this, addr - apu.start_addr, data );

		hes_time_t t = min( time(), end_time() + 8 );
		apu.write_data( t, addr, data );
		return;
	}

	hes_time_t time = this->time();
	switch ( addr )
	{
	case 0x0000:
	case 0x0002:
	case 0x0003:
		cpu_write_vdp( addr, data );
		return;

	case 0x0C00: {
		run_until( time );
		timer.raw_load = (data & 0x7F) + 1;
		recalc_timer_load();
		timer.count = timer.load;
		break;
	}

	case 0x0C01:
		data &= 1;
		if ( timer.enabled == data )
			return;
		run_until( time );
		timer.enabled = data;
		if ( data )
			timer.count = timer.load;
		break;

	case 0x1402:
		run_until( time );
		irq.disables = data;
		if ( (data & 0xF8) && (data & 0xF8) != 0xF8 )
			debug_printf( "Int mask: $%02X\n", data );
		break;

	case 0x1403:
		run_until( time );
		if ( timer.enabled )
			timer.count = timer.load;
		timer.fired = false;
		break;

#ifndef NDEBUG
	case 0x1000:
	case 0x0402:
	case 0x0403:
	case 0x0404:
	case 0x0405:
		return;

	default:
		debug_printf( "unmapped write $%04X <- $%02X\n", addr, data );
		return;
#endif
	}

	irq_changed();
}
