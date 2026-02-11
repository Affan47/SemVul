showsafe(unsigned char *buf, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		if (buf[i] == '\r' || buf[i] == '\n') {
			putchar('\n');
			showcolumn = 0;
		}
		else if (buf[i] < 32 || buf[i] > 126) {
			putchar('.');
			showcolumn ++;
		}
		else {
			putchar(buf[i]);
			showcolumn ++;
		}
		if (showcolumn == 79) {
			putchar('\n');
			showcolumn = 0;
		}
	}
}
