build_callno_limits(struct ast_variable *v)
{
	struct addr_range *addr_range = NULL;
	struct addr_range tmp;
	struct ast_ha *ha;
	int limit;
	int error;
	int found;

	for (; v; v = v->next) {
		limit = -1;
		error = 0;
		found = 0;
		ha = ast_append_ha("permit", v->name, NULL, &error);


		if (error) {
			ast_log(LOG_ERROR, "Call number limit for %s could not be added, Invalid address range\n.", v->name);
			continue;
		} else if ((sscanf(v->value, "%d", &limit) != 1) || (limit < 0)) {
			ast_log(LOG_ERROR, "Call number limit for %s could not be added. Invalid limit %s\n.", v->name, v->value);
			ast_free_ha(ha);
			continue;
		}

		ast_copy_ha(ha, &tmp.ha);

		if ((addr_range = ao2_find(callno_limits, &tmp, OBJ_POINTER))) {
			ao2_lock(addr_range);
			found = 1;
		} else if (!(addr_range = ao2_alloc(sizeof(*addr_range), NULL))) {
			ast_free_ha(ha);
			return;
		}


		ast_copy_ha(ha, &addr_range->ha);
		ast_free_ha(ha);
		addr_range->limit = limit;
		addr_range->delme = 0;


		if (found) {
			ao2_unlock(addr_range);
		} else {
			ao2_link(callno_limits, addr_range);
		}
		ao2_ref(addr_range, -1);
	}
}
