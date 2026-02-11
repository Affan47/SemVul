dev_init(void)
{
	ListIterator i;
	subsystem_t *sub;
	int rc;

	splatctl_fd = open(SPLAT_DEV, O_RDONLY);
	if (splatctl_fd == -1) {
		fprintf(stderr, "Unable to open %s: %d\n"
		        "Is the splat module loaded?\n", SPLAT_DEV, errno);
		rc = errno;
		goto error;
	}


	memset(splat_version, 0, VERSION_SIZE);
	if ((rc = read(splatctl_fd, splat_version, VERSION_SIZE - 1)) == -1)
		goto error;

	if ((rc = dev_clear()))
		goto error;

	if ((rc = dev_size(0)) < 0)
		goto error;

	splat_buffer_size = rc;
	splat_buffer = (char *)malloc(splat_buffer_size);
	if (splat_buffer == NULL) {
		rc = -ENOMEM;
		goto error;
	}

	memset(splat_buffer, 0, splat_buffer_size);


	if ((rc = subsystem_setup()) != 0)
		goto error;


	i = list_iterator_create(subsystems);

	while ((sub = list_next(i))) {
		if ((rc = test_setup(sub)) != 0) {
			list_iterator_destroy(i);
			goto error;
		}
	}

	list_iterator_destroy(i);
	return 0;

error:
	if (splatctl_fd != -1) {
		if (close(splatctl_fd) == -1) {
			fprintf(stderr, "Unable to close %s: %d\n",
		                SPLAT_DEV, errno);
		}
	}

	return rc;
}
