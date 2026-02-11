recvvar(fd, varp)
int fd;
char ***varp;
{
	char *cp, **var;
	int i, c;

	if (recvbuf(fd, &var, sizeof(var)) < 0) return(-1);
	if (var) {
		if (recvbuf(fd, &c, sizeof(c)) < 0) return(-1);
		var = (char **)Xmalloc((c + 1) * sizeof(char *));
		for (i = 0; i < c; i++) {
			if (recvstring(fd, &cp) < 0) {
				var[i] = NULL;
				freevar(var);
				return(-1);
			}
			var[i] = cp;
		}
		var[i] = NULL;
	}
	*varp = var;

	return(0);
}
