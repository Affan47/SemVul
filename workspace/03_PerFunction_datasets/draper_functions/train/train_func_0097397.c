snd_pcm_plug_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
	snd_pcm_plug_t *plug = pcm->private_data;
	snd_pcm_t *slave = plug->req_slave;
	snd_pcm_plug_params_t clt_params, slv_params;
	snd_pcm_hw_params_t sparams;
	int err;

	err = snd_pcm_plug_hw_refine_sprepare(pcm, &sparams);
	if (err < 0)
		return err;
	err = snd_pcm_plug_hw_refine_schange(pcm, params, &sparams);
	if (err < 0)
		return err;
	err = snd_pcm_hw_refine_soft(slave, &sparams);
	if (err < 0)
		return err;

	INTERNAL(snd_pcm_hw_params_get_access)(params, &clt_params.access);
	INTERNAL(snd_pcm_hw_params_get_format)(params, &clt_params.format);
	INTERNAL(snd_pcm_hw_params_get_channels)(params, &clt_params.channels);
	INTERNAL(snd_pcm_hw_params_get_rate)(params, &clt_params.rate, 0);

	INTERNAL(snd_pcm_hw_params_get_format)(&sparams, &slv_params.format);
	INTERNAL(snd_pcm_hw_params_get_channels)(&sparams, &slv_params.channels);
	INTERNAL(snd_pcm_hw_params_get_rate)(&sparams, &slv_params.rate, 0);
	snd_pcm_plug_clear(pcm);
	if (!(clt_params.format == slv_params.format &&
	      clt_params.channels == slv_params.channels &&
	      clt_params.rate == slv_params.rate &&
	      !plug->ttable &&
	      snd_pcm_hw_params_test_access(slave, &sparams,
					    clt_params.access) >= 0)) {
		INTERNAL(snd_pcm_hw_params_set_access_first)(slave, &sparams, &slv_params.access);
		err = snd_pcm_plug_insert_plugins(pcm, &clt_params, &slv_params);
		if (err < 0)
			return err;
	}
	slave = plug->gen.slave;
	err = _snd_pcm_hw_params(slave, params);
	if (err < 0) {
		snd_pcm_plug_clear(pcm);
		return err;
	}
	snd_pcm_unlink_hw_ptr(pcm, plug->req_slave);
	snd_pcm_unlink_appl_ptr(pcm, plug->req_slave);
	snd_pcm_link_hw_ptr(pcm, slave);
	snd_pcm_link_appl_ptr(pcm, slave);
	return 0;
}
