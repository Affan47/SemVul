place(Rune *sp, Rune *l1, Rune *l2)
{

	while(l1 < l2) {
		*sp++ = *l1++;
		if(sp >= &genbuf[LBSIZE])
			error(Q);
	}
	return sp;
}
