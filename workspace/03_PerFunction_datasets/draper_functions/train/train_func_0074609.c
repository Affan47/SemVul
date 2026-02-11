setup_fm()
{
	long ym2612_rate = GET_LE32( header().ym2612_rate );
	long ym2413_rate = GET_LE32( header().ym2413_rate );
	if ( ym2413_rate && GET_LE32( header().version ) < 0x110 )
		update_fm_rates( &ym2413_rate, &ym2612_rate );

	uses_fm = false;

	fm_rate = blip_buf.sample_rate() * oversample_factor;

	if ( ym2612_rate )
	{
		uses_fm = true;
		if ( disable_oversampling_ )
			fm_rate = ym2612_rate / 144.0;
		Dual_Resampler::setup( fm_rate / blip_buf.sample_rate(), rolloff, fm_gain * gain() );
		RETURN_ERR( ym2612.set_rate( fm_rate, ym2612_rate ) );
		ym2612.enable( true );
		set_voice_count( 8 );
	}

	if ( !uses_fm && ym2413_rate )
	{
		uses_fm = true;
		if ( disable_oversampling_ )
			fm_rate = ym2413_rate / 72.0;
		Dual_Resampler::setup( fm_rate / blip_buf.sample_rate(), rolloff, fm_gain * gain() );
		int result = ym2413.set_rate( fm_rate, ym2413_rate );
		if ( result == 2 )
			return "YM2413 FM sound isn't supported";
		CHECK_ALLOC( !result );
		ym2413.enable( true );
		set_voice_count( 8 );
	}

	if ( uses_fm )
	{
		RETURN_ERR( Dual_Resampler::reset( blip_buf.length() * blip_buf.sample_rate() / 1000 ) );
		psg.volume( 0.135 * fm_gain * gain() );
	}
	else
	{
		ym2612.enable( false );
		ym2413.enable( false );
		psg.volume( gain() );
	}

	return 0;
}
