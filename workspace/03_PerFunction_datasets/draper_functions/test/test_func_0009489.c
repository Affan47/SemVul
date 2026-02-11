y_set(struct SYMBOL *s,
	   int up,
	   float x,
	   float w,
	   float y)
{
	struct STAFF_S *p_staff;
	int i, j;

	p_staff = &staff_tb[s->staff];
	i = (int) (x / realwidth * YSTEP);
if (i < 0) {
fprintf(stderr, "y_set i:%d\n", i);
i = 0;
}
	j = (int) ((x + w) / realwidth * YSTEP);
	if (j >= YSTEP) {

		j = YSTEP - 1;
		if (i > j)
			i = j;
	}
	if (up) {
		while (i <= j) {
			if (p_staff->top[i] < y)
				p_staff->top[i] = y;
			i++;
		}
	} else {
		while (i <= j) {
			if (p_staff->bot[i] > y)
				p_staff->bot[i] = y;
			i++;
		}
	}
}
