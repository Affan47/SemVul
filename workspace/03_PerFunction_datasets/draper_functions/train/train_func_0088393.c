tolocal(int argc, char **argv)
{
	int i;
	char *bp, *host, *src, *suser;

	for (i = 0; i < argc - 1; i++) {
		int ret;

		if (!(src = colon(argv[i]))) {
			ret = asprintf(&bp, "exec %s%s%s %s %s", _PATH_CP,
			    iamrecursive ? " -PR" : "", pflag ? " -p" : "",
			    argv[i], argv[argc - 1]);
			if (ret == -1)
				err (1, "malloc");
			if (susystem(bp))
				++errs;
			free(bp);
			continue;
		}
		*src++ = 0;
		if (*src == 0)
			src = ".";
		if ((host = strchr(argv[i], '@')) == NULL) {
			host = argv[i];
			suser = pwd->pw_name;
		} else {
			*host++ = 0;
			suser = argv[i];
			if (*suser == '\0')
				suser = pwd->pw_name;
			else if (!okname(suser))
				continue;
		}
		ret = asprintf(&bp, "%s -f %s", cmd, src);
		if (ret == -1)
			err (1, "malloc");
		if (do_cmd(host, suser, bp, &remin, &remout) < 0) {
			free(bp);
			++errs;
			continue;
		}
		free(bp);
		sink(1, argv + argc - 1);
		close(remin);
		remin = remout = -1;
	}
}
