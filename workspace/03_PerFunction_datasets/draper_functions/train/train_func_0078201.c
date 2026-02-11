k_set_scanning_parameters(KodakAio_Scanner * s)
{
	SANE_Status status;
	unsigned char rs, source;
	SANE_Int scan_pixels_per_line = 0;
	int dpi, optres;

	dpi = s->val[OPT_RESOLUTION].w;
	optres = s->hw->cap->optical_res;


	for (rs=0; rs < s->hw->cap->res_list_size; rs++ ) {
		if ( dpi == s->hw->cap->res_list[rs] )
			break;
	}


	if (strcmp(source_list[s->val[OPT_SOURCE].w], ADF_STR) == 0) {
		source = 0x00;
	} else {
		source = 0x01;
	}


	status = cmd_set_scanning_parameters(s, dpi,
		s->left * dpi / optres, s->top * dpi / optres,
		s->params.pixels_per_line, s->params.lines,
		source);

	if (status != SANE_STATUS_GOOD)
		DBG (1, "%s: Command cmd_set_scanning_parameters failed, %s\n",
		     __func__, sane_strstatus(status));


	status = cmd_get_scanning_parameters (s,
			&s->params.format, &s->params.depth,
			&scan_pixels_per_line,
			&s->params.pixels_per_line, &s->params.lines);
	if (status != SANE_STATUS_GOOD) {
		DBG (1, "%s: Command cmd_get_scanning_parameters failed, %s\n",
		     __func__, sane_strstatus(status));
		return status;
	}


	s->params.bytes_per_line = ceil (s->params.pixels_per_line * s->params.depth / 8.0);
	if (s->val[OPT_MODE].w == MODE_COLOR)
		s->params.bytes_per_line *= 3;


	s->scan_bytes_per_line = 3 * ceil (scan_pixels_per_line * s->params.depth / 8.0);
	s->data_len = s->scan_bytes_per_line * floor (s->height * dpi / optres + 0.5);
	DBG (1, "Check: scan_bytes_per_line = %d  s->params.bytes_per_line = %d \n", s->scan_bytes_per_line, s->params.bytes_per_line);


	status = k_setup_block_mode (s);
	if (status != SANE_STATUS_GOOD)
		DBG (1, "%s: Command k_setup_block_mode failed, %s\n",
		     __func__, sane_strstatus(status));

	DBG (18, "%s: bytes_read_in_line: %d\n", __func__, s->bytes_read_in_line);
	return status;
}
