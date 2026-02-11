ufinish(BW *bw)
{
	unsigned char *line;
	unsigned char *line1;
	unsigned char **lst;
	P *p;
	int c;
	MENU *m;


	if (!piseol(bw->cursor)) {
		int c = brch(bw->cursor);
		if (joe_isalnum_(bw->b->o.charmap,c))
			return -1;
	}


	p = pdup(bw->cursor, USTR "ufinish");
	do
		c = prgetc(p);
		while (joe_isalnum_(bw->b->o.charmap,c));
	if (c!=NO_MORE_DATA)
		pgetc(p);

	if (bw->cursor->byte!=p->byte && bw->cursor->byte-p->byte<64) {
		line = brvs(p, bw->cursor->byte-p->byte);


		if (word_list)
			varm(word_list);

		word_list = get_word_list(bw->b, p->byte);

		if (!word_list) {
			vsrm(line);
			prm(p);
			return -1;
		}

		line1 = vsncpy(NULL,0,sv(line));
		line1 = vsadd(line1,'*');
		lst = regsub(word_list, aLEN(word_list), line1);
		vsrm(line1);

		if (!lst) {
			ttputc(7);
			vsrm(line);
			return -1;
		}

		m = mkmenu(bw->parent, bw->parent, lst, fcmplt_rtn, fcmplt_abrt, NULL, 0, line, NULL);
		if (!m) {
			varm(lst);
			vsrm(line);
			return -1;
		}


		if (aLEN(lst) == 1)
			return fcmplt_rtn(m, 0, line);
		else if (smode)
			return 0;
		else {
			unsigned char *com = mcomplete(m);
			vsrm(m->object);
			m->object = com;
			wabort(m->parent);
			smode = 2;
			ttputc(7);
			return 0;
		}
	} else {
		prm(p);
		return -1;
	}
}
