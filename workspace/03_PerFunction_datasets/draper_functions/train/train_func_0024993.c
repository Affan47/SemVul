nscroll(SCRN *t)
{
	int y, z, q, r, p;

	for (y = 0; y != t->li; ++y) {
		q = t->sary[y];
		if (ifhave)
			return;
		if (q && q != t->li) {
			if (q > 0) {
				for (z = y; z != t->li && t->sary[z] == q; ++z)
					t->sary[z] = 0;
				doupscrl(t, y, z + q, q);
				y = z - 1;
			} else {
				for (r = y; r != t->li && (t->sary[r] < 0 || t->sary[r] == t->li); ++r) ;
				p = r - 1;
				do {
					q = t->sary[p];
					if (q && q != t->li) {
						for (z = p; t->sary[z] = 0, (z && t->sary[z - 1] == q); --z) ;
						dodnscrl(t, z + q, p + 1, -q);
						p = z + 1;
					}
				} while (p-- != y);
				y = r - 1;
			}
		}
	}
	msetI(t->sary, 0, t->li);
}
