cexpr_name_state_get_cur_type(const qpol_iterator_t * iter)
{
	cexpr_name_state_t *cns = NULL;
	const policydb_t *db = NULL;
	char *tmp = NULL, *name = NULL;
	size_t len = 0;

	if (!iter || !(cns = (cexpr_name_state_t *) qpol_iterator_state(iter)) ||
	    !(db = qpol_iterator_policy(iter)) || qpol_iterator_end(iter)) {
		errno = EINVAL;
		return NULL;
	}

	tmp = strdup(db->p_type_val_to_name[cns->cur]);

	if (cns->list == QPOL_CEXPR_NAME_STATE_INC_LIST)
		return tmp;

	len = strlen(tmp);
	name = calloc(len + 2, sizeof(char));
	if (!name) {
		free(tmp);
		errno = ENOMEM;
		return NULL;
	}
	len++;

	snprintf(name, len + 1, "-%s", tmp);
	free(tmp);

	return name;
}
