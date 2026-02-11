qpol_type_set_get_included_types_iter(const qpol_policy_t * policy, const qpol_type_set_t * ts, qpol_iterator_t ** iter)
{
	type_set_t *internal_ts = NULL;
	ebitmap_state_t *es = NULL;
	int error = 0;

	if (iter)
		*iter = NULL;

	if (!policy || !ts || !iter) {
		ERR(policy, "%s", strerror(EINVAL));
		error = EINVAL;
		return STATUS_ERR;
	}

	internal_ts = (type_set_t *) ts;

	es = calloc(1, sizeof(ebitmap_state_t));
	if (!es) {
		error = errno;
		ERR(policy, "%s", strerror(error));
		errno = error;
		return STATUS_ERR;
	}

	es->bmap = &(internal_ts->types);
	es->cur = es->bmap->node ? es->bmap->node->startbit : 0;

	if (qpol_iterator_create(policy, es, ebitmap_state_get_cur_type,
				 ebitmap_state_next, ebitmap_state_end, ebitmap_state_size, free, iter)) {
		free(es);
		return STATUS_ERR;
	}

	if (es->bmap->node && !ebitmap_get_bit(es->bmap, es->cur))
		ebitmap_state_next(*iter);

	return STATUS_SUCCESS;
}
