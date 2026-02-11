alsa_seq_oss_init(void)
{
	int rc;

	if ((rc = register_device()) < 0)
		goto error;
	if ((rc = register_proc()) < 0) {
		unregister_device();
		goto error;
	}
	if ((rc = snd_seq_oss_create_client()) < 0) {
		unregister_proc();
		unregister_device();
		goto error;
	}

	rc = snd_seq_driver_register(&seq_oss_synth_driver);
	if (rc < 0) {
		snd_seq_oss_delete_client();
		unregister_proc();
		unregister_device();
		goto error;
	}


	snd_seq_oss_synth_init();

 error:
	return rc;
}
