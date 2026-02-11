link_module(policydb_t * base, FILE * out_fp)
{
	char module_name[80] = { 0 };
	int ret;
	policydb_t module, *mods = &module;

	if (base->policy_type != POLICY_BASE) {
		printf("Can only link if initial file was a base policy.\n");
		return;
	}
	printf("\nModule filename: ");
	fgets(module_name, sizeof(module_name), stdin);
	module_name[strlen(module_name) - 1] = '\0';
	if (module_name[0] == '\0') {
		return;
	}


	fprintf(out_fp, "Reading module...\n");
	if (read_policy(module_name, mods)) {
		fprintf(stderr,
			"%s:  error(s) encountered while loading policy\n",
			module_name);
		exit(1);
	}
	if (module.policy_type != POLICY_MOD) {
		fprintf(stderr, "This file is not a loadable policy module.\n");
		exit(1);
	}
	if (policydb_index_classes(&module) ||
	    policydb_index_others(NULL, &module, 0)) {
		fprintf(stderr, "Could not index module.\n");
		exit(1);
	}
	ret = link_modules(NULL, base, &mods, 1, 0);
	if (ret != 0) {
		printf("Link failed (error %d)\n", ret);
		printf("(You will probably need to restart dismod.)\n");
	}
	policydb_destroy(&module);
	return;
}
