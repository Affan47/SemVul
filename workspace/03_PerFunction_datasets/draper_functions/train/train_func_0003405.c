alloc_frame_data(struct ccd_frame *fr)
{
	if (!fr->dat) {
		if ((fr->dat = malloc(fr->w * fr->h * fr->pix_size)) == NULL)
			return ERR_ALLOC;
	}

	return 0;
}
