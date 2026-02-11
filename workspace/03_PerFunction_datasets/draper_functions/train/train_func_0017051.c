start_track_( int track )
{
	RETURN_ERR( Classic_Emu::start_track_( track ) );

	memset( ram, 0, sizeof ram );
	memset( sgx, 0, sizeof sgx );

	apu.reset();
	cpu::reset();

	for ( unsigned i = 0; i < sizeof header_.banks; i++ )
		set_mmr( i, header_.banks [i] );
	set_mmr( page_count, 0xFF );

	irq.disables  = timer_mask | vdp_mask;
	irq.timer     = future_hes_time;
	irq.vdp       = future_hes_time;

	timer.enabled = false;
	timer.raw_load= 0x80;
	timer.count   = timer.load;
	timer.fired   = false;
	timer.last_time = 0;

	vdp.latch     = 0;
	vdp.control   = 0;
	vdp.next_vbl  = 0;

	ram [0x1FF] = (idle_addr - 1) >> 8;
	ram [0x1FE] = (idle_addr - 1) & 0xFF;
	r.sp = 0xFD;
	r.pc = GET_LE16( header_.init_addr );
	r.a  = track;

	recalc_timer_load();
	last_frame_hook = 0;

	return 0;
}
