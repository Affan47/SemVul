test_loop_setup(const char *filename, const char *device)
{
	struct loopdev_cxt lc;
	int rc = 0;

	loopcxt_init(&lc, 0);

	if (device) {
		rc = loopcxt_set_device(&lc, device);
		if (rc)
			err(EXIT_FAILURE, "failed to set device: %s", device);
	}

	do {
		if (!device) {
			rc = loopcxt_find_unused(&lc);
			if (rc)
				err(EXIT_FAILURE, "failed to find unused device");
			printf("Trying to use '%s'\n", loopcxt_get_device(&lc));
		}

		if (loopcxt_set_backing_file(&lc, filename))
			err(EXIT_FAILURE, "failed to set backing file");

		rc = loopcxt_setup_device(&lc);
		if (rc == 0)
			break;

		if (device || rc != -EBUSY)
			err(EXIT_FAILURE, "failed to setup device for %s",
					lc.filename);

		printf("device stolen...trying again\n");
	} while (1);

	loopcxt_deinit(&lc);

	return 0;
}
