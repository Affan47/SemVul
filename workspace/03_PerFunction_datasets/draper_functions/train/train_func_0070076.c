searchb(BW *bw,SRCH *srch, P *p)
{
	unsigned char *pattern = srch->pattern;
	P *start;
	P *end;
	int x;

	start = pdup(p);
	end = pdup(p);

	for (x = 0; x != sLEN(pattern) && pattern[x] != '\\' && (pattern[x]<128 || !p->b->o.charmap->type); ++x)
		if (srch->ignore)
			pattern[x] = joe_tolower(p->b->o.charmap,pattern[x]);

	wrapped:
	while (pbkwd(start, 1L)
	       && (srch->ignore ? prifind(start, pattern, x) : prfind(start, pattern, x))) {
		pset(end, start);
		pfwrd(end, (long) x);
		if (srch->wrap_flag && start->byte<srch->wrap_p->byte)
			break;
		if (pmatch(srch->pieces, pattern + x, sLEN(pattern) - x, end, 0, srch->ignore)) {
			srch->entire = vstrunc(srch->entire, (int) (end->byte - start->byte));
			brmem(start, srch->entire, (int) (end->byte - start->byte));
			pset(p, start);
			prm(start);
			prm(end);
			return p;
		}
	}

	if (wrap && !srch->wrap_flag && srch->wrap_p) {
		msgnw(bw->parent, US "Wrapped");
		srch->wrap_flag = 1;
		p_goto_eof(start);
		goto wrapped;
	}

	prm(start);
	prm(end);
	return NULL;
}
