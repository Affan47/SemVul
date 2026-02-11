check_lib_paths(struct role_acl *role, struct proc_acl *def_acl)
{
	FILE *ldconf;
	char buf[PATH_MAX];
	struct stat fstat;
	struct chk_perm chk;
	unsigned int errs_found = 0;

	if ((ldconf = fopen("/etc/ld.so.conf", "r")) == NULL)
		return 0;

	chk.type = CHK_FILE;
	chk.u_modes = GR_WRITE;
	chk.w_modes = 0xffff;

	while (fgets(buf, PATH_MAX - 1, ldconf)) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';

		if (!stat(buf, &fstat)
		    && !check_permission(role, def_acl, buf, &chk)) {
			fprintf(stderr,
				"Write access is allowed by role %s to %s, a directory which "
				"holds libraries for your system and is included "
				"in /etc/ld.so.conf.\n\n", role->rolename, buf);
			errs_found++;
		}
	}

	fclose(ldconf);

	return errs_found;
}
