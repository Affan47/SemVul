apol_string_vector_t_remove(apol_string_vector_t *self,size_t idx){
		BEGIN_EXCEPTION
		char *x = apol_vector_get_element((apol_vector_t*)self, idx);
		if (apol_vector_remove((apol_vector_t*)self, idx)) {
			{SWIG_JavaException(local_jenv, SWIG_RuntimeError, "Error removing vector element"); goto fail;};
		}
		free(x);
		END_EXCEPTION
	fail:
			return;
	}
