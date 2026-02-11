jp2_read_ihdr(opj_jp2_t *jp2, opj_cio_t *cio) {
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	if (JP2_IHDR != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected IHDR Marker\n");
		return false;
	}

	jp2->h = cio_read(cio, 4);
	jp2->w = cio_read(cio, 4);
	jp2->numcomps = cio_read(cio, 2);
	jp2->comps = (opj_jp2_comps_t*) opj_malloc(jp2->numcomps * sizeof(opj_jp2_comps_t));

	jp2->bpc = cio_read(cio, 1);

	jp2->C = cio_read(cio, 1);
	jp2->UnkC = cio_read(cio, 1);
	jp2->IPR = cio_read(cio, 1);

	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with IHDR Box\n");
		return false;
	}

	return true;
}
