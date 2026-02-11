write_data( blip_time_t time, int addr, int data )
{
	if ( addr == 0x800 )
	{
		latch = data & 7;
	}
	else if ( addr == 0x801 )
	{
		if ( balance != data )
		{
			balance = data;

			Hes_Osc* osc = &oscs [osc_count];
			do
			{
				osc--;
				osc->run_until( synth, time );
				balance_changed( *oscs );
			}
			while ( osc != oscs );
		}
	}
	else if ( latch < osc_count )
	{
		Hes_Osc& osc = oscs [latch];
		osc.run_until( synth, time );
		switch ( addr )
		{
		case 0x802:
			osc.period = (osc.period & 0xF00) | data;
			break;

		case 0x803:
			osc.period = (osc.period & 0x0FF) | ((data & 0x0F) << 8);
			break;

		case 0x804:
			if ( osc.control & 0x40 & ~data )
				osc.phase = 0;
			osc.control = data;
			balance_changed( osc );
			break;

		case 0x805:
			osc.balance = data;
			balance_changed( osc );
			break;

		case 0x806:
			data &= 0x1F;
			if ( !(osc.control & 0x40) )
			{
				osc.wave [osc.phase] = data;
				osc.phase = (osc.phase + 1) & 0x1F;
			}
			else if ( osc.control & 0x80 )
			{
				osc.dac = data;
			}
			break;

		 case 0x807:
		 	if ( &osc >= &oscs [4] )
		 		osc.noise = data;
		 	break;

		 case 0x809:
		 	if ( !(data & 0x80) && (data & 0x03) != 0 )
		 		debug_printf( "HES LFO not supported\n" );
		}
	}
}
