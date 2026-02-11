wrap_apol_avrule_list_to_syn_avrules(apol_policy_t *p, apol_vector_t *rules, apol_string_vector_t *perms) {
		apol_vector_t *v;
		BEGIN_EXCEPTION
		v = apol_avrule_list_to_syn_avrules(p, rules, (apol_vector_t*)perms);
		if (!v) {
			SWIG_exception(SWIG_RuntimeError, "Could not convert avrules to syntactic avrules");
		}
		END_EXCEPTION
	fail:
		return v;
	}
