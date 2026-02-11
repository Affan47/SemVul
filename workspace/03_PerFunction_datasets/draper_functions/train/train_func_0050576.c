make_shift_ctrans(struct ctrans *ct, double dx, double dy)
{
	int i,j;

	ct->order = 1;

	for (i = 0; i < MAX_ORDER; i++)
		for (j = 0; j < MAX_ORDER; j++) {
			ct->a[i][j] = 0.0;
			ct->b[i][j] = 0.0;
		}
	ct->u0 = dx;
	ct->v0 = dy;
	ct->a[1][0] = 1.0;
	ct->b[0][1] = 1.0;
	return 0;
}
