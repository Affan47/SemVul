print_child_argv(const char *prefix, char **cmd)
{
	int cnt = 0;
	rprintf(FCLIENT, "%s ", prefix);
	for (; *cmd; cmd++) {


		if (strspn(*cmd, "abcdefghijklmnopqrstuvwxyz"
			   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			   "0123456789"
			   ",.-_=+@/") != strlen(*cmd)) {
			rprintf(FCLIENT, "\"%s\" ", *cmd);
		} else {
			rprintf(FCLIENT, "%s ", *cmd);
		}
		cnt++;
	}
	rprintf(FCLIENT, " (%d args)\n", cnt);
}
