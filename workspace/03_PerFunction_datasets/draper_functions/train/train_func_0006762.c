by_sysfs(char ***br, int *nbr, char *siopt)
{
	int err, i, l, sz;
	char buf[BufSiz], path[] = SiPathPrefix "1234567890123456/br32767";
	char *p, *end, **a, *q;
	FILE *fp;

	errno = EINVAL;
	end = strchr(siopt, ',');
	if (end)
		i = end - siopt;
	else
		i = strlen(siopt);

	strncpy(path + sizeof(SiPathPrefix) - 1, siopt, i);
	p = path + sizeof(SiPathPrefix) - 1 + i;
	strcpy(p, "/br");
	p += 3;
	*nbr = 0;
	err = 0;
	while (!err) {
		sprintf(p, "%d", (*nbr)++);
		err = access(path, F_OK);
	}

	a = malloc(sizeof(*br) * *nbr);
	if (!a)
		AuFin("malloc");

	(*nbr)--;
	*br = a;
	for (i = 0; i < *nbr; i++) {
		sprintf(p, "%d", i);
		fp = fopen(path, "r");
		if (!fp)
			AuFin("%s", path);
		if (fgets(buf, sizeof(buf), fp) != buf)
			AuFin("%s", path);
		l = strlen(buf);
		if (l < 1)
			AuFin("internal error, %d", l);

		q = strndup(buf, l - 1);
		if (buf[l - 1] != '\n') {


			sz = sizeof(buf);
			do {
				free(q);
				sz <<= 1;
				q = malloc(sz);
				if (!q)
					AuFin("malloc");
				rewind(fp);
				if (fgets(q, sz, fp) != q)
					AuFin("%s", path);
				l = strlen(q);
			} while (q[l - 1] != '\n');
			q[l - 1] = 0;
		}

		*a++ = q;

		fclose(fp);
	}
	*a = NULL;

	return 0;
}
