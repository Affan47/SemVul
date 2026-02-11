mygetnstr(char *buf, int maxlen, int doecho)
{
    int c, i;

    i = 0;
    for (;;)
    {
	c = getch();
	if (c == 8 || c == 127 || c == KEY_BACKSPACE || c == KEY_DC ||
		c == KEY_LEFT)
	{
	    if (i > 0)
	    {
		i--;
		if (doecho)
		    addstr("\010 \010");
	    }
	    else
		beep();
	}
	else if (c == 21 || c == 24 || c == KEY_DL)
	{
	    while (i > 0)
	    {
		i--;
		if (doecho)
		    addstr("\010 \010");
	    }
	}
	else if (c == 23)
	{
	    while (i > 0 && buf[i - 1] == ' ')
	    {
		i--;
		if (doecho)
		    addstr("\010 \010");
	    }
	    while (i > 0 && buf[i - 1] != ' ')
	    {
		i--;
		if (doecho)
		    addstr("\010 \010");
	    }
	}
	else if ((c >= ' ' && c <= '~') || (c >= 0xA0 && c <= 0xFF))
	{
	    if (i < maxlen)
	    {
		buf[i] = c;
		i++;
		if (doecho)
		    addch(c);
	    }
	    else
		beep();
	}
	else if (c == 10 || c == 13 || c == KEY_ENTER || c == KEY_RESIZE)
	    break;
	else if (c == ERR)
	{
	    buf[i] = 0;
	    return ERR;
	}
	else
	    beep();
    }
    buf[i] = 0;
    return OK;
}
