opj_destroy_cstr_info(opj_codestream_info_v2_t **cstr_info) {
	if (cstr_info) {

		if ((*cstr_info)->m_default_tile_info.tccp_info){
			opj_free((*cstr_info)->m_default_tile_info.tccp_info);
		}

		if ((*cstr_info)->tile_info){

		}

		opj_free((*cstr_info));
		(*cstr_info) = NULL;
	}
}
