add(char *key, int value) {
	isc_result_t result;
	isc_symvalue_t symvalue;

	if (sym_mctx == NULL) {
		result = isc_mem_create(0, 0, &sym_mctx);
		if (result != ISC_R_SUCCESS)
			return;
	}

	if (symtab == NULL) {
		result = isc_symtab_create(sym_mctx, 100, freekey, sym_mctx,
					   ISC_FALSE, &symtab);
		if (result != ISC_R_SUCCESS)
			return;
	}

	key = isc_mem_strdup(sym_mctx, key);
	if (key == NULL)
		return;

	symvalue.as_pointer = NULL;
	result = isc_symtab_define(symtab, key, value, symvalue,
				   isc_symexists_reject);
	if (result != ISC_R_SUCCESS)
		isc_mem_free(sym_mctx, key);
}
