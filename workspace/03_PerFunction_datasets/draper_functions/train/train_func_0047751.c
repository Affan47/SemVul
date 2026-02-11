apol_perm_query_t_run(apol_perm_query_t *self,apol_policy_t *p){
		apol_vector_t *v;
		BEGIN_EXCEPTION
		if (apol_perm_get_by_query(p, self, &v)) {
			{tcl_throw_error("Could not run permission query"); goto fail;};
		}
		END_EXCEPTION
	fail:
		return (apol_string_vector_t*)v;
	}
