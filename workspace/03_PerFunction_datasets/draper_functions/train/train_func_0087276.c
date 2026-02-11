j2k_read_soc(opj_j2k_t *j2k) {
	j2k->state = J2K_STATE_MHSIZ;

	if (j2k->cstr_info) {
		j2k->cstr_info->main_head_start = cio_tell(j2k->cio) - 2;
		j2k->cstr_info->codestream_size = cio_numbytesleft(j2k->cio) + 2 - j2k->cstr_info->main_head_start;
	}
}
