listCrtcProperties(void)
{
	int i;
	drmModeCrtcPtr c;

	for (i = 0; i < res->count_crtcs; i++) {
		c = drmModeGetCrtc(fd, res->crtcs[i]);

		if (!c) {
			fprintf(stderr, "Could not get crtc %u: %s\n",
				res->crtcs[i], strerror(errno));
			continue;
		}

		printf("CRTC %u\n", c->crtc_id);

		listObjectProperties(c->crtc_id, DRM_MODE_OBJECT_CRTC);

		drmModeFreeCrtc(c);
	}
}
