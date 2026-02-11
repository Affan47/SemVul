parse_crashkernel_suffix(char *cmdline,
					   unsigned long long	*crash_size,
					   const char *suffix)
{
	char *cur = cmdline;

	*crash_size = memparse(cmdline, &cur);
	if (cmdline == cur) {
		pr_warn("crashkernel: memory value expected\n");
		return -EINVAL;
	}


	if (strncmp(cur, suffix, strlen(suffix))) {
		pr_warn("crashkernel: unrecognized char: %c\n", *cur);
		return -EINVAL;
	}
	cur += strlen(suffix);
	if (*cur != ' ' && *cur != '\0') {
		pr_warn("crashkernel: unrecognized char: %c\n", *cur);
		return -EINVAL;
	}

	return 0;
}
