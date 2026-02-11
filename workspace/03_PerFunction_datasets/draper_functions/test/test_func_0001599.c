n_setwd(void)
{
	int base, wid;
	Tchar i;
	int	delim, emsz, k;
	int	savhp, savapts, savapts1, savfont, savfont1, savpts, savpts1;

	base = numtabp[ST].val = numtabp[ST].val = wid = numtabp[CT].val = 0;
	if (ismot(i = getch()))
		return;
	delim = cbits(i);
	savhp = numtabp[HP].val;
	numtabp[HP].val = 0;
	savapts = apts;
	savapts1 = apts1;
	savfont = font;
	savfont1 = font1;
	savpts = pts;
	savpts1 = pts1;
	setwdf++;
	while (cbits(i = getch()) != delim && !nlflg) {
		k = width(i);
		wid += k;
		numtabp[HP].val += k;
		if (!ismot(i)) {
			emsz = (INCH * pts + 36) / 72;
		} else if (isvmot(i)) {
			k = absmot(i);
			if (isnmot(i))
				k = -k;
			base -= k;
			emsz = 0;
		} else
			continue;
		if (base < numtabp[SB].val)
			numtabp[SB].val = base;
		if ((k = base + emsz) > numtabp[ST].val)
			numtabp[ST].val = k;
	}
	setn1(wid, 0, (Tchar) 0);
	numtabp[HP].val = savhp;
	apts = savapts;
	apts1 = savapts1;
	font = savfont;
	font1 = savfont1;
	pts = savpts;
	pts1 = savpts1;
	mchbits();
	setwdf = 0;
}
