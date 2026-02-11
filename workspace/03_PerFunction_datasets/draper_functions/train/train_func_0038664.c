fileexist(const cfg_obj_t *obj, isc_symtab_t *symtab, isc_boolean_t writeable,
	  isc_log_t *logctx)
{
	isc_result_t result;
	isc_symvalue_t symvalue;
	unsigned int line;
	const char *file;

	result = isc_symtab_lookup(symtab, cfg_obj_asstring(obj), 0, &symvalue);
	if (result == ISC_R_SUCCESS) {
		if (writeable) {
			file = cfg_obj_file(symvalue.as_cpointer);
			line = cfg_obj_line(symvalue.as_cpointer);
			cfg_obj_log(obj, logctx, ISC_LOG_ERROR,
				    "writeable file '%s': already in use: "
				    "%s:%u", cfg_obj_asstring(obj),
				    file, line);
			return (ISC_R_EXISTS);
		}
		result = isc_symtab_lookup(symtab, cfg_obj_asstring(obj), 2,
					   &symvalue);
		if (result == ISC_R_SUCCESS) {
			file = cfg_obj_file(symvalue.as_cpointer);
			line = cfg_obj_line(symvalue.as_cpointer);
			cfg_obj_log(obj, logctx, ISC_LOG_ERROR,
				    "writeable file '%s': already in use: "
				    "%s:%u", cfg_obj_asstring(obj),
				    file, line);
			return (ISC_R_EXISTS);
		}
		return (ISC_R_SUCCESS);
	}

	symvalue.as_cpointer = obj;
	result = isc_symtab_define(symtab, cfg_obj_asstring(obj),
				   writeable ? 2 : 1, symvalue,
				   isc_symexists_reject);
	return (result);
}
