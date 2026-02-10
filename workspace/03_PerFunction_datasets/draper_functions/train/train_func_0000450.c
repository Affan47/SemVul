read_ancestry(const char *graft_file)
{
	FILE *fp = fopen(graft_file, "r");
	char buf[1024];
	if (!fp)
		return -1;
	while (fgets(buf, sizeof(buf), fp)) {

		int len = strlen(buf);
		struct commit_graft *graft = read_graft_line(buf, len);
		if (graft)
			register_commit_graft(graft, 0);
	}
	fclose(fp);
	return 0;
}
