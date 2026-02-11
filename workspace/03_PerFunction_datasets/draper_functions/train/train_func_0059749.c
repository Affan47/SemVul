argverify(int ftype, Extsym *p)
#endif
{
	Argtypes *at;
	register Atype *aty;
	int i, j, k;
	register int *t, *te;
	char buf1[32], buf2[32];

	at = p->arginfo;
	if (at->nargs < 0)
		return;
	if (p->extype != ftype) {
		Pbadret(ftype, p);
		return;
		}
	t = tfirst;
	te = tnext;
	i = te - t;
	if (at->nargs != i) {
		j = at->nargs;
		Pbadmsg("differing numbers of arguments",p);
		fprintf(stderr, "here %d, previously %d\n",
			i, j);
		return;
		}
	for(aty = at->atypes; t < te; t++, aty++) {
		if (*t == aty->type)
			continue;
		j = aty->type;
		k = *t;
		if (k >= 300 || k == j)
			continue;
		if (j >= 300) {
			if (k >= 200) {
				if (k == TYUNKNOWN + 200)
					continue;
				if (j % 100 != k - 200
				 && k != TYSUBR + 200
				 && j != TYUNKNOWN + 300
				 && !type_fixup(at,aty,k))
					goto badtypes;
				}
			else if (j % 100 % TYSUBR != k % TYSUBR
					&& !type_fixup(at,aty,k))
				goto badtypes;
			}
		else if (k < 200 || j < 200)
			goto badtypes;
		else if (k == TYUNKNOWN+200)
			continue;
		else if (j != TYUNKNOWN+200)
			{
 badtypes:
			Pbadmsg("differing calling sequences",p);
			i = t - tfirst + 1;
			fprintf(stderr,
				"arg %d: here %s, prevously %s\n",
				i, Argtype(k,buf1), Argtype(j,buf2));
			return;
			}


		aty->type = k;
		at->changes = 1;
		}
	}
