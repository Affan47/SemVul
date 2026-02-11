jp2_read_bpcc(opj_jp2_t *jp2, opj_cio_t *cio) {
	unsigned int i;
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

	jp2_read_boxhdr(cinfo, cio, &box);
	if (JP2_BPCC != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected BPCC Marker\n");
		return false;
	}

	for (i = 0; i < jp2->numcomps; i++) {
		jp2->comps[i].bpcc = cio_read(cio, 1);
	}

	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with BPCC Box\n");
		return false;
	}

	return true;
}
