qpol_terule_t_get_which_list(qpol_terule_t *self,qpol_policy_t *p){
		const qpol_cond_t *c;
		uint32_t which = 0;
		BEGIN_EXCEPTION
		qpol_terule_get_cond(p, self, &c);
		if (c == NULL) {
			{tcl_throw_error("Rule is not conditional"); goto fail;};
		} else if (qpol_terule_get_which_list(p, self, &which)) {
			{tcl_throw_error("Could not get conditional list for te rule"); goto fail;};
		}
		END_EXCEPTION
	fail:
		return (int) which;
	}
