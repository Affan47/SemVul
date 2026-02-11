qpol_constraint_get_expr_iter(const qpol_policy_t * policy, const qpol_constraint_t * constr, qpol_iterator_t ** iter)
{
	constr_expr_state_t *ces = NULL;
	constraint_node_t *internal_constr = NULL;

	if (iter)
		*iter = NULL;

	if (!policy || !constr || !iter) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_constr = (constraint_node_t *) constr->constr;

	if (!(ces = calloc(1, sizeof(constr_expr_state_t)))) {
		ERR(policy, "%s", strerror(ENOMEM));
		errno = ENOMEM;
		return STATUS_ERR;
	}
	ces->head = ces->cur = internal_constr->expr;

	if (qpol_iterator_create(policy, (void *)ces,
				 constr_expr_state_get_cur, constr_expr_state_next,
				 constr_expr_state_end, constr_expr_state_size, free, iter)) {
		free(ces);
		return STATUS_ERR;
	}

	return STATUS_SUCCESS;
}
