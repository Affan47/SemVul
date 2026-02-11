new_apol_policy_path_t__SWIG_2(char *str,int unused){
		apol_policy_path_t *p;
		BEGIN_EXCEPTION
		if ((p = apol_policy_path_create_from_string(str)) == NULL) {
			{tcl_throw_error("Out of memory"); goto fail;};
		}
		END_EXCEPTION
	fail:
			return p;
	}
