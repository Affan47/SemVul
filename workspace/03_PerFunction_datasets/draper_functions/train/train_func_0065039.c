reduce_frames(struct image_file_list *imfl, struct ccd_reduce *ccdr,
		  int (* progress)(char *msg, void *data), void *data)
{
	GList *gl;
	struct image_file *imf;
	char msg[256];
	int ret = 0;

	if (ccdr->ops & IMG_OP_BIAS) {
		if (ccdr->bias == NULL) {
			err_printf("no bias image file\n");
			return 1;
		}
		if (load_image_file(ccdr->bias))
			return 2;
		snprintf(msg, 255, "bias frame: %s\n", ccdr->bias->filename);
		if (progress) {
			if ((*progress)(msg, data))
				return -1;
		}
	}
	if (ccdr->ops & IMG_OP_DARK) {
		if (ccdr->dark == NULL) {
			err_printf("no dark image file\n");
			return 1;
		}
		if (load_image_file(ccdr->dark))
			return 2;
		snprintf(msg, 255, "dark frame: %s\n", ccdr->dark->filename);
		if (progress) {
			if ((*progress)(msg, data))
				return -1;
		}
	}
	if (ccdr->ops & IMG_OP_FLAT) {
		if (ccdr->flat == NULL) {
			err_printf("no flat image file\n");
			return 1;
		}
		if (load_image_file(ccdr->flat))
			return 2;
		snprintf(msg, 255, "flat frame: %s\n", ccdr->flat->filename);
		if (progress) {
			if ((*progress)(msg, data))
				return -1;
		}
	}

	gl = imfl->imlist;
	while (gl != NULL) {
		imf = gl->data;
		gl = g_list_next(gl);
		if (imf->flags & IMG_SKIP)
			continue;
		if (progress) {
			if ((*progress)(imf->filename, data))
				return -1;
		}
		if (load_image_file(imf)) {
			err_printf("frame will be skipped\n");
			imf->flags |= IMG_SKIP;
			continue;
		}

		if (progress) {
			if ((*progress)(" loaded", data))
				return -1;
		}
		ret = ccd_reduce_imf(imf, ccdr, progress, data);
	}
	return ret;
}
