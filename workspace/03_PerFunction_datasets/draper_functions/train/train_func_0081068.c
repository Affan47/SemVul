combine_diff(const unsigned char *parent, unsigned int mode,
			 mmfile_t *result_file,
			 struct sline *sline, unsigned int cnt, int n,
			 int num_parent, int result_deleted,
			 struct userdiff_driver *textconv,
			 const char *path)
{
	unsigned int p_lno, lno;
	unsigned long nmask = (1UL << n);
	xpparam_t xpp;
	xdemitconf_t xecfg;
	mmfile_t parent_file;
	struct combine_diff_state state;
	unsigned long sz;

	if (result_deleted)
		return;

	parent_file.ptr = grab_blob(parent, mode, &sz, textconv, path);
	parent_file.size = sz;
	memset(&xpp, 0, sizeof(xpp));
	xpp.flags = 0;
	memset(&xecfg, 0, sizeof(xecfg));
	memset(&state, 0, sizeof(state));
	state.nmask = nmask;
	state.sline = sline;
	state.lno = 1;
	state.num_parent = num_parent;
	state.n = n;

	xdi_diff_outf(&parent_file, result_file, consume_line, &state,
		      &xpp, &xecfg);
	free(parent_file.ptr);


	for (lno = 0,  p_lno = 1; lno <= cnt; lno++) {
		struct lline *ll;
		sline[lno].p_lno[n] = p_lno;


		ll = sline[lno].lost_head;
		while (ll) {
			if (ll->parent_map & nmask)
				p_lno++;
			ll = ll->next;
		}
		if (lno < cnt && !(sline[lno].flag & nmask))
			p_lno++;
	}
	sline[lno].p_lno[n] = p_lno;
}
