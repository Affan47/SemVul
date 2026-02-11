qual_syscall(const char *s, int bitflag, int not)
{
	int i;
	int rc = -1;

	if (isdigit((unsigned char)*s)) {
		int i = atoi(s);
		if (i < 0 || i >= MAX_QUALS)
			return -1;
		qualify_one(i, bitflag, not, -1);
		return 0;
	}
	for (i = 0; i < nsyscalls0; i++)
		if (strcmp(s, sysent0[i].sys_name) == 0) {
			qualify_one(i, bitflag, not, 0);
			rc = 0;
		}

#if SUPPORTED_PERSONALITIES >= 2
	for (i = 0; i < nsyscalls1; i++)
		if (strcmp(s, sysent1[i].sys_name) == 0) {
			qualify_one(i, bitflag, not, 1);
			rc = 0;
		}
#endif

#if SUPPORTED_PERSONALITIES >= 3
	for (i = 0; i < nsyscalls2; i++)
		if (strcmp(s, sysent2[i].sys_name) == 0) {
			qualify_one(i, bitflag, not, 2);
			rc = 0;
		}
#endif

	return rc;
}
