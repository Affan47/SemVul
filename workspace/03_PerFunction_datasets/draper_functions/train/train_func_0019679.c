seaudit_log_t_get_users(seaudit_log_t *self){
		apol_vector_t *v;
		BEGIN_EXCEPTION
		v = seaudit_log_get_users(self);
		if (!v) {
			{tcl_throw_error("Out of memory"); goto fail;};
		}
		END_EXCEPTION
	fail:
		return (apol_string_vector_t*)v;
	}
