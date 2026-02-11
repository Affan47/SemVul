time1(struct ast_tm *tmp, struct ast_tm * (* const funcp) (const struct timeval *, long, struct ast_tm *, const struct state *), const long offset, const struct state *sp)
{
	struct timeval			t;
	int			samei, otheri;
	int			sameind, otherind;
	int			i;
	int			nseen;
	int				seen[TZ_MAX_TYPES];
	int				types[TZ_MAX_TYPES];
	int				okay;

	if (tmp->tm_isdst > 1)
		tmp->tm_isdst = 1;
	t = time2(tmp, funcp, offset, &okay, sp);
#ifdef PCTS


	if (okay)
		return t;
	if (tmp->tm_isdst < 0)
		tmp->tm_isdst = 0;
#endif
#ifndef PCTS
	if (okay || tmp->tm_isdst < 0)
		return t;
#endif


	if (sp == NULL)
		return WRONG;
	for (i = 0; i < sp->typecnt; ++i)
		seen[i] = FALSE;
	nseen = 0;
	for (i = sp->timecnt - 1; i >= 0; --i)
		if (!seen[sp->types[i]]) {
			seen[sp->types[i]] = TRUE;
			types[nseen++] = sp->types[i];
		}
	for (sameind = 0; sameind < nseen; ++sameind) {
		samei = types[sameind];
		if (sp->ttis[samei].tt_isdst != tmp->tm_isdst)
			continue;
		for (otherind = 0; otherind < nseen; ++otherind) {
			otheri = types[otherind];
			if (sp->ttis[otheri].tt_isdst == tmp->tm_isdst)
				continue;
			tmp->tm_sec += sp->ttis[otheri].tt_gmtoff -
					sp->ttis[samei].tt_gmtoff;
			tmp->tm_isdst = !tmp->tm_isdst;
			t = time2(tmp, funcp, offset, &okay, sp);
			if (okay)
				return t;
			tmp->tm_sec -= sp->ttis[otheri].tt_gmtoff -
					sp->ttis[samei].tt_gmtoff;
			tmp->tm_isdst = !tmp->tm_isdst;
		}
	}
	return WRONG;
}
