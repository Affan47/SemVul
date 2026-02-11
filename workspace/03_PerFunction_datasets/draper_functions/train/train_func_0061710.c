text_yank(char *p, char *q, int dest)
{
	int cnt = q - p;
	if (cnt < 0) {
		p = q;
		cnt = -cnt;
	}
	free(reg[dest]);
	reg[dest] = xstrndup(p, cnt + 1);
	return p;
}
