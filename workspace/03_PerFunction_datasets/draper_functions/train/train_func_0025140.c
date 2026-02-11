combine_diff(const unsigned char *parent, mmfile_t *result_file,
			 struct sline *sline, unsigned int cnt, int n,
			 int num_parent)
{
	unsigned int p_lno, lno;
	unsigned long nmask = (1UL << n);
	xpparam_t xpp;
	xdemitconf_t xecfg;
	mmfile_t parent_file;
	xdemitcb_t ecb;
	struct combine_diff_state state;
	unsigned long sz;

	if (!cnt)
		return;

	parent_file.ptr = grab_blob(parent, &sz);
	parent_file.size = sz;
	xpp.flags = XDF_NEED_MINIMAL;
	xecfg.ctxlen = 0;
	xecfg.flags = 0;
	ecb.outf = xdiff_outf;
	ecb.priv = &state;
	memset(&state, 0, sizeof(state));
	state.xm.consume = consume_line;
	state.nmask = nmask;
	state.sline = sline;
	state.lno = 1;
	state.num_parent = num_parent;
	state.n = n;

	xdl_diff(&parent_file, result_file, &xpp, &xecfg, &ecb);
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
