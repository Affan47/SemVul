cob_unstring_init (cob_field *src, cob_field *ptr, const size_t num_dlm)
{
	static size_t	udlmcount = 0;

	unstring_src_copy = *src;
	unstring_src = &unstring_src_copy;
	unstring_ptr = NULL;
	if (ptr) {
		unstring_ptr_copy = *ptr;
		unstring_ptr = &unstring_ptr_copy;
	}

	unstring_offset = 0;
	unstring_count = 0;
	unstring_ndlms = 0;
	cob_exception_code = 0;
	if (!dlm_list) {
		if (num_dlm <= DLM_DEFAULT_NUM) {
			dlm_list = cob_malloc (DLM_DEFAULT_NUM * sizeof(struct dlm_struct));
			udlmcount = DLM_DEFAULT_NUM;
		} else {
			dlm_list = cob_malloc (num_dlm * sizeof(struct dlm_struct));
			udlmcount = num_dlm;
		}
	} else {
		if (num_dlm > udlmcount) {
			free (dlm_list);
			dlm_list = cob_malloc (num_dlm * sizeof(struct dlm_struct));
			udlmcount = num_dlm;
		}
	}

	if (unstring_ptr) {
		unstring_offset = cob_get_int (unstring_ptr) - 1;
		if (unstring_offset < 0 || unstring_offset >= (int)unstring_src->size) {
			cob_set_exception (COB_EC_OVERFLOW_UNSTRING);
		}
	}
}
