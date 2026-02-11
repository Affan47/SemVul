init(unsigned short * wc, int len)
{
	for (int i = 0; i < MAXPREVLINE; i++) {
		line[i][0] = '\0';
	}
	actual = 0;
	head = 0;
	token = 0;
	state = 0;
	utf8 = 1;
	checkurl = 0;
        wordchars_utf16 = wc;
        wclen = len;
}
