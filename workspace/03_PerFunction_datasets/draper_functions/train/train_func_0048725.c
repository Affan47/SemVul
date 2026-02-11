new_icxcam(icxCAM which) {
	icxcam *s;

	if ((s = (icxcam *)calloc(1, sizeof(icxcam))) == NULL) {
		fprintf(stderr,"icxcam: malloc failed allocating object\n");
		return NULL;
	}


	s->del      = icx_cam_free;
	s->set_view = icx_set_view;
	s->XYZ_to_cam = icx_XYZ_to_cam;
	s->cam_to_XYZ = icx_cam_to_XYZ;
	s->settrace   = settrace;


	if (which == cam_default)
		which = icxcam_default();

	s->tag = which;

	switch(which) {
		case cam_CIECAM97s3:
			if ((s->p = (void *)new_cam97s3()) == NULL) {
				fprintf(stderr,"icxcam: malloc failed allocating object\n");
				free(s);
				return NULL;
			}
			break;
		case cam_CIECAM02:
			if ((s->p = (void *)new_cam02()) == NULL) {
				fprintf(stderr,"icxcam: malloc failed allocating object\n");
				free(s);
				return NULL;
			}
			break;

		default:
			fprintf(stderr,"icxcam: unknown CAM type\n");
			free(s);
			return NULL;
	}
	return s;
}
