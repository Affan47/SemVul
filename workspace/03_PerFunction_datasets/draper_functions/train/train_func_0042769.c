Iterate_X2(ATTRACTOR * A, PRM x, PRM y, PRM * xo, PRM * yo)
{
	PRM         xx, yy, xy, x2y, y2x, Tmp;

	xx = (x * x) / UNIT;
	x2y = (xx * y) / UNIT;
	yy = (y * y) / UNIT;
	y2x = (yy * x) / UNIT;
	xy = (x * y) / UNIT;

	Tmp = A->Prm[1] * xx + A->Prm[2] * xy + A->Prm[3] * yy + A->Prm[4] * x2y;
	Tmp = A->Prm[0] - y + (Tmp / UNIT);
	*xo = DO_FOLD(Tmp);
	Tmp = A->Prm[6] * xx + A->Prm[7] * xy + A->Prm[8] * yy + A->Prm[9] * y2x;
	Tmp = A->Prm[5] + x + (Tmp / UNIT);
	*yo = DO_FOLD(Tmp);
}
