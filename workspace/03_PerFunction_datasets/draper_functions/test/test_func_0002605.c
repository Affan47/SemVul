qpol_constraint_get_perm_iter(const qpol_policy_t * policy, const qpol_constraint_t * constr, qpol_iterator_t ** iter)
{
	perm_state_t *ps = NULL;
	constraint_node_t *internal_constr = NULL;

	if (iter)
		*iter = NULL;

	if (!policy || !constr || !iter) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_constr = (constraint_node_t *) constr->constr;

	if (!(ps = calloc(1, sizeof(perm_state_t)))) {
		ERR(policy, "%s", strerror(ENOMEM));
		errno = ENOMEM;
	}
	ps->perm_set = internal_constr->permissions;
	qpol_class_get_value(policy, constr->obj_class, &ps->obj_class_val);

	if (qpol_iterator_create(policy, (void *)ps, perm_state_get_cur,
				 perm_state_next, perm_state_end, perm_state_size, free, iter)) {
		free(ps);
		return STATUS_ERR;
	}

	if (!(ps->perm_set & 1))
		qpol_iterator_next(*iter);

	return STATUS_SUCCESS;
}
