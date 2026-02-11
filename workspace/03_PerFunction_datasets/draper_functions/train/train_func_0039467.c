jp2_read_jp(opj_jp2_t *jp2, opj_cio_t *cio) {
	opj_jp2_box_t box;

	opj_common_ptr cinfo = jp2->cinfo;

  if( jp2_read_boxhdr(cinfo, cio, &box) == OPJ_FALSE ) {
    opj_event_msg(cinfo, EVT_ERROR, "Failed to read boxhdr\n");
    return OPJ_FALSE;
  }
	if (JP2_JP != box.type) {
		opj_event_msg(cinfo, EVT_ERROR, "Expected JP Marker\n");
		return OPJ_FALSE;
	}
	if (0x0d0a870a != cio_read(cio, 4)) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with JP Marker\n");
		return OPJ_FALSE;
	}
	if (cio_tell(cio) - box.init_pos != box.length) {
		opj_event_msg(cinfo, EVT_ERROR, "Error with JP Box size\n");
		return OPJ_FALSE;
	}

	return OPJ_TRUE;
}
