andor(void)
{
	union node *n1, *n2, *n3;
	int t;

	n1 = pipeline();
	for (;;) {
		t = readtoken();
		if (t == TAND) {
			t = NAND;
		} else if (t == TOR) {
			t = NOR;
		} else {
			tokpushback = 1;
			return n1;
		}
		checkkwd = CHKNL | CHKKWD | CHKALIAS;
		n2 = pipeline();
		n3 = stzalloc(sizeof(struct nbinary));
		n3->type = t;
		n3->nbinary.ch1 = n1;
		n3->nbinary.ch2 = n2;
		n1 = n3;
	}
}
