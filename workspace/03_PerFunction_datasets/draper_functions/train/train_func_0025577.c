find_realtime(const char *name)
{
	struct ast_variable *var;
	struct ast_variable *v;
	struct ast_config *cfg;
	const char *catg;
	struct call_followme *new_follower;
	struct ast_str *str;

	str = ast_str_create(16);
	if (!str) {
		return NULL;
	}

	var = ast_load_realtime("followme", "name", name, SENTINEL);
	if (!var) {
		ast_free(str);
		return NULL;
	}

	if (!(new_follower = alloc_profile(name))) {
		ast_variables_destroy(var);
		ast_free(str);
		return NULL;
	}

	for (v = var; v; v = v->next) {
		if (!strcasecmp(v->name, "active")) {
			if (ast_false(v->value)) {
				ast_mutex_destroy(&new_follower->lock);
				ast_free(new_follower);
				ast_variables_destroy(var);
				ast_free(str);
				return NULL;
			}
		} else {
			profile_set_param(new_follower, v->name, v->value, 0, 0);
		}
	}

	ast_variables_destroy(var);
	new_follower->realtime = 1;


	cfg = ast_load_realtime_multientry("followme_numbers", "ordinal LIKE", "%", "name",
		name, SENTINEL);
	if (!cfg) {
		ast_mutex_destroy(&new_follower->lock);
		ast_free(new_follower);
		ast_free(str);
		return NULL;
	}

	for (catg = ast_category_browse(cfg, NULL); catg; catg = ast_category_browse(cfg, catg)) {
		const char *numstr;
		const char *timeoutstr;
		const char *ordstr;
		int timeout;
		struct number *cur;

		if (!(numstr = ast_variable_retrieve(cfg, catg, "phonenumber"))) {
			continue;
		}
		if (!(timeoutstr = ast_variable_retrieve(cfg, catg, "timeout"))
			|| sscanf(timeoutstr, "%30d", &timeout) != 1
			|| timeout < 1) {
			timeout = 25;
		}

		ordstr = ast_variable_retrieve(cfg, catg, "ordinal");
		ast_str_set(&str, 0, "%s", numstr);
		if ((cur = create_followme_number(ast_str_buffer(str), timeout, atoi(ordstr)))) {
			AST_LIST_INSERT_TAIL(&new_follower->numbers, cur, entry);
		}
	}
	ast_config_destroy(cfg);

	ast_free(str);
	return new_follower;
}
