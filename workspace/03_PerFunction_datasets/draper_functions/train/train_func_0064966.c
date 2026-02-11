dump_connectors_fd(int drmfd)
{
	int i, j;

	drmModeRes *mode_resources = drmModeGetResources(drmfd);

	if (!mode_resources) {
		fprintf(stderr, "drmModeGetResources failed: %s\n",
			strerror(errno));
		return;
	}

	printf("Connectors:\n");
	printf("id\tencoder\tstatus\t\ttype\tsize (mm)\tmodes\n");
	for (i = 0; i < mode_resources->count_connectors; i++) {
		drmModeConnector *connector;

		connector = drmModeGetConnector(drmfd, mode_resources->connectors[i]);
		if (!connector) {
			fprintf(stderr, "could not get connector %i: %s\n",
				mode_resources->connectors[i], strerror(errno));
			continue;
		}

		printf("%d\t%d\t%s\t%s\t%dx%d\t\t%d\n",
		       connector->connector_id,
		       connector->encoder_id,
		       connector_status_str(connector->connection),
		       connector_type_str(connector->connector_type),
		       connector->mmWidth, connector->mmHeight,
		       connector->count_modes);

		if (!connector->count_modes)
			continue;

		printf("  modes:\n");
		printf("  name refresh (Hz) hdisp hss hse htot vdisp "
		       "vss vse vtot flags type clock\n");
		for (j = 0; j < connector->count_modes; j++)
			kmstest_dump_mode(&connector->modes[j]);

		drmModeFreeConnector(connector);
	}
	printf("\n");

	drmModeFreeResources(mode_resources);
}
