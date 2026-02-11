write_pcm( vgm_time_t vgm_time, int amp )
{
	blip_time_t blip_time = to_blip_time( vgm_time );
	int old = dac_amp;
	int delta = amp - old;
	dac_amp = amp;
	if ( old >= 0 )
		dac_synth.offset_inline( blip_time, delta, &blip_buf );
	else
		dac_amp |= dac_disabled;
}
