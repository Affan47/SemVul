qpol_policy_destroy(qpol_policy_t ** policy)
{
	if (policy != NULL && *policy != NULL) {
		sepol_policydb_free((*policy)->p);
		sepol_handle_destroy((*policy)->sh);
		qpol_extended_image_destroy(&((*policy)->ext));
		if ((*policy)->modules) {
			size_t i = 0;
			for (i = 0; i < (*policy)->num_modules; i++) {
				qpol_module_destroy(&((*policy)->modules[i]));
			}
			free((*policy)->modules);
		}
		if ((*policy)->file_data_type == QPOL_POLICY_FILE_DATA_TYPE_MEM) {
			free((*policy)->file_data);
		} else if ((*policy)->file_data_type == QPOL_POLICY_FILE_DATA_TYPE_MMAP) {
			munmap((*policy)->file_data, (*policy)->file_data_sz);
		}
		free(*policy);
		*policy = NULL;
	}
}
