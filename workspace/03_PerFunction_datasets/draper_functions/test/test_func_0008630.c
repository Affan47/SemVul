storeCurrentMonthHistory(char *f, int s, int r, double b)
{
	hist h[MAXMONTHS];
	int i;

	if (f == NULL)
		return;
	for (i = 0; i < MAXMONTHS; i++) {
		h[i].sent = 0;
		h[i].received = 0;
		h[i].bytes_sent = 0;
	}

	getHistData(f, h, sizeof(h));

	h[cur_month - 1].sent = s;
	h[cur_month - 1].received = r;
	h[cur_month - 1].bytes_sent = b;

	storeHistData(f, h, sizeof(h));
}
