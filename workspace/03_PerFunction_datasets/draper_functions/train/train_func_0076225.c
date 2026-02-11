unlink_all(const char *dir)
{
	char cmd[strlen(dir) + sizeof("rm -rf ")];
	sprintf(cmd, "rm -rf %s", dir);
	if (tools_verbose)
		printf("Running: %s\n", cmd);
	if (system(cmd) != 0)
		warn("Could not remove temporary work in %s", dir);
	return 0;
}
