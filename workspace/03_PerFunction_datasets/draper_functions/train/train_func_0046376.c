stats_add_scope(struct uri_auth **root, char *scope)
{
	struct uri_auth *u;
	char *new_name;
	struct stat_scope *old_scope, **scope_list;

	if ((u = stats_check_init_uri_auth(root)) == NULL)
		goto out;

	scope_list = &u->scope;
	while ((old_scope = *scope_list)) {
		if (!strcmp(old_scope->px_id, scope))
			break;
		scope_list = &old_scope->next;
	}

	if (!old_scope) {
		if ((new_name = strdup(scope)) == NULL)
			goto out_u;

		if ((old_scope = (struct stat_scope *)calloc(1, sizeof(*old_scope))) == NULL)
			goto out_name;

		old_scope->px_id = new_name;
		old_scope->px_len = strlen(new_name);
		*scope_list = old_scope;
	}
	return u;

 out_name:
	free(new_name);
 out_u:
	free(u);
 out:
	return NULL;
}
