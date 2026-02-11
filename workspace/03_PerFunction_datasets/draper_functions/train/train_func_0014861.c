gr_dup(const struct group *gr)
{
	char *dst;
	size_t len;
	struct group_storage *gs;
	int ndx;
	int num_mem;


	len = sizeof(*gs);
	if (gr->gr_name != NULL)
		len += strlen(gr->gr_name) + 1;
	if (gr->gr_passwd != NULL)
		len += strlen(gr->gr_passwd) + 1;
	if (gr->gr_mem != NULL) {
		for (num_mem = 0; gr->gr_mem[num_mem] != NULL; num_mem++)
			len += strlen(gr->gr_mem[num_mem]) + 1;
		len += (num_mem + 1) * sizeof(*gr->gr_mem);
	} else
		num_mem = -1;


	if ((gs = calloc(1, len)) == NULL)
		return (NULL);
	dst = (char *)&gs->members[num_mem + 1];
	if (gr->gr_name != NULL) {
		gs->gr.gr_name = dst;
		dst = stpcpy(gs->gr.gr_name, gr->gr_name) + 1;
	}
	if (gr->gr_passwd != NULL) {
		gs->gr.gr_passwd = dst;
		dst = stpcpy(gs->gr.gr_passwd, gr->gr_passwd) + 1;
	}
	gs->gr.gr_gid = gr->gr_gid;
	if (gr->gr_mem != NULL) {
		gs->gr.gr_mem = gs->members;
		for (ndx = 0; ndx < num_mem; ndx++) {
			gs->gr.gr_mem[ndx] = dst;
			dst = stpcpy(gs->gr.gr_mem[ndx], gr->gr_mem[ndx]) + 1;
		}
		gs->gr.gr_mem[ndx] = NULL;
	}

	return (&gs->gr);
}
