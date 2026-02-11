start_track_( int track )
{
	RETURN_ERR( Classic_Emu::start_track_( track ) );
	psg.reset( GET_LE16( header().noise_feedback ), header().noise_width );

	dac_disabled = -1;
	pos          = data + header_size;
	pcm_data     = pos;
	pcm_pos      = pos;
	dac_amp      = -1;
	vgm_time     = 0;
	if ( GET_LE32( header().version ) >= 0x150 )
	{
		long data_offset = GET_LE32( header().data_offset );
		check( data_offset );
		if ( data_offset )
			pos += data_offset + offsetof (header_t,data_offset) - 0x40;
	}

	if ( uses_fm )
	{
		if ( ym2413.enabled() )
			ym2413.reset();

		if ( ym2612.enabled() )
			ym2612.reset();

		fm_time_offset = 0;
		blip_buf.clear();
		Dual_Resampler::clear();
	}
	return 0;
}
