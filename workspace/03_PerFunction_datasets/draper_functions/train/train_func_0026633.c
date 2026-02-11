snd_rme9652_set_defaults(struct snd_rme9652 *rme9652)
{
	unsigned int k;


	rme9652->control_register =
	    RME9652_inp_0 | rme9652_encode_latency(7);

	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);

	rme9652_reset_hw_pointer(rme9652);
	rme9652_compute_period_size(rme9652);


	for (k = 0; k < RME9652_NCHANNELS; ++k)
		rme9652_write(rme9652, RME9652_thru_base + k * 4, 0);

	rme9652->thru_bits = 0;
	rme9652->passthru = 0;


	rme9652_set_rate(rme9652, 48000);
}
