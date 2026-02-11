parseit(struct charmap *map,unsigned char *s, long int row,
  void (*parseone)(struct charmap *map, unsigned char *s, unsigned char **rtn_name, long *rtn_line))
{
	unsigned char *name = NULL;
	long line = -1;
	ERROR *err;

	parseone(map,s,&name,&line);

	if (name) {
		if (line != -1) {

			err = (ERROR *) alitem(&errnodes, sizeof(ERROR));
			err->file = name;
			err->org = err->line = line;
			err->src = row;
			err->msg = vsncpy(NULL, 0, sc("\\i"));
			err->msg = vsncpy(sv(err->msg), sv(s));
			enqueb(ERROR, link, &errors, err);
			return 1;
		} else
			vsrm(name);
	}
	return 0;
}
