snd_use_case_mgr_reload(snd_use_case_mgr_t *uc_mgr)
{
	int err;

	pthread_mutex_lock(&uc_mgr->mutex);

	uc_mgr_free_verb(uc_mgr);


	err = import_master_config(uc_mgr);
	if (err < 0) {
		uc_error("error: failed to reload use cases\n");
		pthread_mutex_unlock(&uc_mgr->mutex);
		return -EINVAL;
	}

	pthread_mutex_unlock(&uc_mgr->mutex);
	return err;
}
