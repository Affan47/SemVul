askfor_aux(char *buf, size_t len, bool keypress_h(char *, size_t, size_t *, size_t *, char, bool))
{
	int y, x;

	size_t k = 0;
	size_t nul = 0;

	char ch = '\0';

	bool done = FALSE;
	bool firsttime = TRUE;

	if (keypress_h == NULL)
	{
		keypress_h = askfor_aux_keypress;
	}


	Term_locate(&x, &y);


	if ((x < 0) || (x >= 80)) x = 0;


	if (x + len > 80) len = 80 - x;


	buf[len-1] = '\0';


	nul = strlen(buf);


	Term_erase(x, y, (int)len);
	Term_putstr(x, y, -1, TERM_YELLOW, buf);


	while (!done)
	{

		Term_gotoxy(x + k, y);


		ch = inkey();


		done = keypress_h(buf, len, &k, &nul, ch, firsttime);


		Term_erase(x, y, (int)len);
		Term_putstr(x, y, -1, TERM_WHITE, buf);


		firsttime = FALSE;
	}


	return (ch != ESCAPE);
}
