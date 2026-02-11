tinytest_set_flag_(struct testgroup_t *groups, const char *arg, unsigned long flag)
{
	int i, j;
	size_t length = LONGEST_TEST_NAME;
	char fullname[LONGEST_TEST_NAME];
	int found=0;
	if (strstr(arg, ".."))
		length = strstr(arg,"..")-arg;
	for (i=0; groups[i].prefix; ++i) {
		for (j=0; groups[i].cases[j].name; ++j) {
			snprintf(fullname, sizeof(fullname), "%s%s",
				 groups[i].prefix, groups[i].cases[j].name);
			if (!flag)
				printf("    %s\n", fullname);
			if (!strncmp(fullname, arg, length)) {
				groups[i].cases[j].flags |= flag;
				++found;
			}
		}
	}
	return found;
}
