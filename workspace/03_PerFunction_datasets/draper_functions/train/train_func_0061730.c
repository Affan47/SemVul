mybytemap(map)
int map[];
{
	union {
		of_t o;
		char c[SOF];
	} u;
	register int *mp = &map[SOF];
	register int ntodo;
	register int i;

	u.o = 1;
	for (ntodo = (int)SOF; ntodo > 0; ntodo--) {
		for (i = 0; i < SOF; i++)

			if (u.c[i] != 0)
				break;
		if (i == SOF) {

			DEBUG(("mybytemap: nonexistent byte %d!!!\n", ntodo));
			for (i = 0; i < SOF; i++)
				map[i] = i;
			return;
		}
		DEBUG(("mybytemap: byte %d\n", i));
		*--mp = i;

		while (u.c[i] != 0)
			u.o <<= 1;
	}
}
