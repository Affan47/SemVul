new_apol_policy_path_t__SWIG_0(apol_policy_path_type_e type,char *primary,apol_string_vector_t *modules){
		apol_policy_path_t *p;
		BEGIN_EXCEPTION
		if ((p = apol_policy_path_create(type, primary,	(apol_vector_t*)modules)) == NULL) {
			{tcl_throw_error("Out of memory"); goto fail;};
		}
		END_EXCEPTION
	fail:
		return p;
	}
