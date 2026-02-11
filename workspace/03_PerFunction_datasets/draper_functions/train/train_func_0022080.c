jack_server_initialize_shm (int new_registry)
{
	int rc;

	if (jack_shm_header)
		return 0;

	if (jack_shm_lock_registry () < 0) {
        jack_error ("jack_shm_lock_registry fails...");
        return -1;
    }

	rc = jack_access_registry (&registry_info);

	if (new_registry) {
		jack_remove_shm (&registry_id);
		rc = ENOENT;
	}

	switch (rc) {
	case ENOENT:
		rc = jack_create_registry (&registry_info);
		break;
	case 0:
		if (jack_shm_validate_registry () == 0)
			break;

	case EINVAL:


		jack_release_shm (&registry_info);
		jack_remove_shm (&registry_id);
		if ((rc = jack_create_registry (&registry_info)) != 0) {
			jack_error ("incompatible shm registry (%s)",
				    strerror (errno));
#ifndef USE_POSIX_SHM
			jack_error ("to delete, use `ipcrm -M 0x%0.8x'",
				    JACK_SHM_REGISTRY_KEY);
#endif
		}
		break;
	default:
		break;
	}

	jack_shm_unlock_registry ();
	return rc;
}
