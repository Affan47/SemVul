DrawCities(struct state *st, int xlim, int ylim)
{
  int i, x;
  for (i = 0; i < kNumCities; i++) {
	 City *m = &st->city[i];
	 if (!m->alive)
		continue;
	 x = (i + 1) * (xlim / (kNumCities + 1));
	 m->x = x;

	 DrawCity(st, x, ylim, m->color);
  }
}
