dosub(void)
{
	Rune *lp, *sp, *rp;
	int c, n;

	lp = linebuf;
	sp = genbuf;
	rp = rhsbuf;
	while(lp < loc1)
		*sp++ = *lp++;
	while(c = *rp++) {
		if(c == '&'){
			sp = place(sp, loc1, loc2);
			continue;
		}
		if(c == ESCFLG && (c = *rp++) >= '1' && c < MAXSUB+'0') {
			n = c-'0';
			if(subexp[n].s.rsp && subexp[n].e.rep) {
				sp = place(sp, subexp[n].s.rsp, subexp[n].e.rep);
				continue;
			}
			error(Q);
		}
		*sp++ = c;
		if(sp >= &genbuf[LBSIZE])
			error(Q);
	}
	lp = loc2;
	loc2 = sp - genbuf + linebuf;
	while(*sp++ = *lp++)
		if(sp >= &genbuf[LBSIZE])
			error(Q);
	lp = linebuf;
	sp = genbuf;
	while(*lp++ = *sp++)
		;
}
