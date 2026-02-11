qpol_policy_get_terule_iter(const qpol_policy_t * policy, uint32_t rule_type_mask, qpol_iterator_t ** iter)
{
	policydb_t *db;
	avtab_state_t *state;

	if (iter) {
		*iter = NULL;
	}
	if (policy == NULL || iter == NULL) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

#if 1
	if (!qpol_policy_has_capability(policy, QPOL_CAP_RULES_LOADED)) {
		ERR(policy, "%s", "Cannot get terules: Rules not loaded");
		errno = ENOTSUP;
		return STATUS_ERR;
	}
#endif

	db = &policy->p->p;

	state = calloc(1, sizeof(avtab_state_t));
	if (state == NULL) {
		ERR(policy, "%s", strerror(ENOMEM));
		errno = ENOMEM;
		return STATUS_ERR;
	}
	state->ucond_tab = &db->te_avtab;
	state->cond_tab = &db->te_cond_avtab;
	state->rule_type_mask = rule_type_mask;
	state->node = db->te_avtab.htable[0];

	if (qpol_iterator_create
	    (policy, state, avtab_state_get_cur, avtab_state_next, avtab_state_end, avtab_state_size, free, iter)) {
		free(state);
		return STATUS_ERR;
	}
	if (state->node == NULL || !(state->node->key.specified & state->rule_type_mask)) {
		avtab_state_next(*iter);
	}
	return STATUS_SUCCESS;
}
