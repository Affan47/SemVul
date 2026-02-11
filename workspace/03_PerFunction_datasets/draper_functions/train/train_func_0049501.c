find_domains_get_list(sechk_module_t * mod, apol_policy_t * policy, void *arg)
{
	apol_vector_t **v = arg;

	if (!mod || !arg) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return -1;
	}
	if (strcmp(mod_name, mod->name)) {
		ERR(policy, "Wrong module (%s)", mod->name);
		errno = EINVAL;
		return -1;
	}
	if (!mod->result) {
		ERR(policy, "%s", "Module has not been run");
		errno = EINVAL;
		return -1;
	}

	v = &mod->result->items;

	return 0;
}
