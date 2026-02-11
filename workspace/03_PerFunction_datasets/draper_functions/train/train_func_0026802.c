is_compress_trans() {
	return ses.keys->trans_algo_comp == DROPBEAR_COMP_ZLIB
		|| (ses.authstate.authdone
			&& ses.keys->trans_algo_comp == DROPBEAR_COMP_ZLIB_DELAY);
}
