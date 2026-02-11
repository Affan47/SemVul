dosdirfooter(bsizep, nf, nd, sump, bsump, fp, tp)
off_t *bsizep;
int nf, nd;
off_t *sump, *bsump, *fp, *tp;
#endif
{
	if (dirtype == 'B') return;
	if (!nf && !nd) {
		if (!fp) return;
		if (checkline(1) < 0) return;
		Xfputs("File not found\n", Xstdout);
		nd = -1;
	}
	else {
		if (fp && (dirflag & DF_SUBDIR)) {
			if (checkline(1) < 0) return;
			VOID_C fputnl(Xstdout);
			if (checkline(1) < 0) return;
			Xfputs("Total files listed:\n", Xstdout);
		}
		if (checkline(1) < 0) return;
		VOID_C Xprintf("%10d file(s)%'15qd bytes\n", nf, *sump);
#ifndef	MINIMUMSHELL
		if (dirtype == 'V') {
			if (checkline(1) < 0) return;
			VOID_C Xprintf("%10d dir(s) ", nd);
			fputsize(bsump, bsizep);
			Xfputs(" allocated\n", Xstdout);
			nd = -1;
		}
#endif
	}
	if (!fp) return;

	if (checkline(1) < 0) return;
	if (nd < 0) Xfputs("                  ", Xstdout);
	else VOID_C Xprintf("%10d dir(s) ", nd);

	fputsize(fp, bsizep);
	Xfputs(" free\n", Xstdout);

#ifndef	MINIMUMSHELL
	if (tp && dirtype == 'V') {
		if (checkline(1) < 0) return;
		Xfputs("                  ", Xstdout);
		fputsize(tp, bsizep);
		VOID_C Xprintf(" total disk space, %3d%% in use\n",
			(int)(((*tp - *fp) * (off_t)100) / *tp));
	}
#endif
}
