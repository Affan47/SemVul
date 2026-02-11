radio_init(char *device, DriverType driver)
{
	int rv = -1;
	void *md;
	const char *p = NULL;

	md = discover_media_devices();

	if (autodetect) {
		*device = 0;
		if (!md) {
			fprintf (stderr, "open: Failed to open \"auto\" device");
			if (*device)
				fprintf (stderr, " at %s\n", device);
			else
				fprintf (stderr, "\n");
			goto failure;
		}

		while (1) {
			p = get_associated_device(md, p, MEDIA_V4L_RADIO, NULL, NONE);
			if (!p)
				break;
			asprintf(&device, "/dev/%s", p);
		}

		p = NULL;
	}

	if (!md) {
		fprintf (stderr, "open: Failed to open radio device %s\n", device);
		goto failure;
	}

	switch (driver) {
		case DRIVER_ANY:
		case DRIVER_V4L2:
		default:
			goto try_v4l2;
		case DRIVER_V4L1:
			goto try_v4l1;
	}

try_v4l1:
	dev = v4l1_radio_dev_new();
	rv = dev->init (dev, device);
	if (rv == 0) {
        	fprintf(stderr, "v4l1: Initialization failed\n");
		dev->finalize (dev);
		dev = NULL;
		can_capture = 0;
		if (alsa_loopback)
			alsa_loopback = 0;
		if (driver != DRIVER_ANY)
			goto failure;
	} else {
		goto success;
	}

try_v4l2:
	dev = v4l2_radio_dev_new();
	rv = dev->init (dev, device);
	if (rv == 0) {
        	fprintf(stderr, "v4l2: Initialization failed\n");
		dev->finalize (dev);
		dev = NULL;
		can_capture = 0;
		if (alsa_loopback)
			alsa_loopback = 0;
		if (driver != DRIVER_ANY)
			goto failure;
	} else {
		goto success;
	}

success:
	if (autodetect)
		fprintf(stderr, "open: Using radio device: %s\n", device);

	p = strrchr(device, '/');
	if (p)
		p++;
	else
		p = device;

	p = get_associated_device(md, NULL, MEDIA_SND_CAP, p, MEDIA_V4L_RADIO);
	if (p) {
		can_capture = 1;
		if (alsa_loopback && alsa_capture == NULL)
			alsa_capture = strdup(p);
		p = NULL;
	} else {
		can_capture = 0;
		if (alsa_loopback)
			alsa_loopback = 0;
	}

	if (alsa_loopback) {
		if (alsa_playback == NULL)
			alsa_playback = "default";

		fprintf(stderr, "alsa: Stream started from %s (%s) to %s\n",
			alsa_capture, device, alsa_playback);
	}

	radio_unmute();

failure:
	if (autodetect)
		free (device);
	if (md)
		free_media_devices(md);

	return rv;
}
