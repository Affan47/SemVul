kdb_exec_defcmd(int argc, const char **argv)
{
	int i, ret;
	struct defcmd_set *s;
	if (argc != 0)
		return KDB_ARGCOUNT;
	for (s = defcmd_set, i = 0; i < defcmd_set_count; ++i, ++s) {
		if (strcmp(s->name, argv[0]) == 0)
			break;
	}
	if (i == defcmd_set_count) {
		kdb_printf("kdb_exec_defcmd: could not find commands for %s\n",
			   argv[0]);
		return KDB_NOTIMP;
	}
	for (i = 0; i < s->count; ++i) {


		argv = NULL;
		kdb_printf("[%s]kdb> %s\n", s->name, s->command[i]);
		ret = kdb_parse(s->command[i]);
		if (ret)
			return ret;
	}
	return 0;
}
