sortlists (SQUARE *ws, SQ_CONTENT *wp)
{
	int i, j;
	SQUARE ts;
	SQ_CONTENT tp;

	for (i = 0; wp[i] != NOPIECE; i++) {
		for (j = (i+1); wp[j] != NOPIECE; j++) {
			if (wp[j] > wp[i]) {
				tp = wp[i]; wp[i] = wp[j]; wp[j] = tp;
				ts = ws[i]; ws[i] = ws[j]; ws[j] = ts;
			}
		}
	}
}
