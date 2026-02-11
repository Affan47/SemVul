apol_domain_trans_analysis_t_run(apol_domain_trans_analysis_t *self,apol_policy_t *p){
		apol_vector_t *v = NULL;
		BEGIN_EXCEPTION
		if (apol_domain_trans_analysis_do(p, self, &v)) {
			{SWIG_JavaException(local_jenv, SWIG_RuntimeError, "Could not run domain transition analysis"); goto fail;};
		}
		END_EXCEPTION
	fail:
		return v;
	}
