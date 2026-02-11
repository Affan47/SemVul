free_servtab_strings(servtab_t *cp)
{
	int i;

	free(cp->se_local_hostname);
	free(cp->se_service);
	free(cp->se_proto);
	free(cp->se_user);
	free(cp->se_group);
	free(cp->se_lsa);
	free(cp->se_program);
	for (i = 0; i < MAXARGV; i++)
		free(cp->se_argv[i]);
}
