seaudit_model_t_append_filter(seaudit_model_t *self,seaudit_filter_t *filter){
		BEGIN_EXCEPTION

		seaudit_filter_t *tmp = seaudit_filter_create_from_filter(filter);
		if (seaudit_model_append_filter(self, tmp)) {
			seaudit_filter_destroy(&tmp);
			{SWIG_JavaException(local_jenv, SWIG_RuntimeError, "Could not append filter to model"); goto fail;};
		}


		END_EXCEPTION
	fail:
		return;
	}
