qpol_policy_append_module(qpol_policy_t * policy, qpol_module_t * module)
{
	qpol_module_t **tmp = NULL;
	int error = 0;

	if (!policy || !module) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	if (!(tmp = realloc(policy->modules, (1 + policy->num_modules) * sizeof(qpol_module_t *)))) {
		error = errno;
		ERR(policy, "%s", strerror(error));
		errno = error;
		return STATUS_ERR;
	}

	policy->modules = tmp;
	policy->modules[policy->num_modules] = module;
	policy->num_modules++;
	policy->modified = 1;
	module->parent = policy;

	return STATUS_SUCCESS;
}
