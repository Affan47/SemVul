jack_access_registry (jack_shm_info_t *ri)
{

	int shm_fd;

	strncpy (registry_id, "/jack-shm-registry", sizeof (registry_id));


	if ((shm_fd = shm_open (registry_id, O_RDWR, 0666)) < 0) {
		int rc = errno;
		if (errno != ENOENT) {
			jack_error ("Cannot open existing shm registry segment"
				    " (%s)", strerror (errno));
		}
		close (shm_fd);
		return rc;
	}

	if ((ri->ptr.attached_at = mmap (0, JACK_SHM_REGISTRY_SIZE,
				     PROT_READ|PROT_WRITE,
				     MAP_SHARED, shm_fd, 0)) == MAP_FAILED) {
		jack_error ("Cannot mmap shm registry segment (%s)",
			    strerror (errno));
		close (shm_fd);
		return EINVAL;
	}


	ri->index = JACK_SHM_REGISTRY_INDEX;
	jack_shm_header = ri->ptr.attached_at;
	jack_shm_registry = (jack_shm_registry_t *) (jack_shm_header + 1);

	close (shm_fd);
	return 0;
}
