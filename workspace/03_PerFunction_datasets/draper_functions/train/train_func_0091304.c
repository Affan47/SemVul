qpol_policy_get_range_trans_iter(const qpol_policy_t * policy, qpol_iterator_t ** iter)
{
	policydb_t *db = NULL;
	range_trans_state_t *rs = NULL;
	int error = 0;

	if (iter)
		*iter = NULL;

	if (!policy || !iter) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	db = &policy->p->p;

	rs = calloc(1, sizeof(range_trans_state_t));
	if (!rs) {
		error = errno;
		ERR(policy, "%s", strerror(error));
		errno = error;
		return STATUS_ERR;
	}

	if (qpol_iterator_create(policy, (void *)rs, range_trans_state_get_cur,
				 range_trans_state_next, range_trans_state_end, range_trans_state_size, free, iter)) {
		error = errno;
		free(rs);
		errno = error;
		return STATUS_ERR;
	}

	rs->head = rs->cur = db->range_tr;
	return STATUS_SUCCESS;
}
