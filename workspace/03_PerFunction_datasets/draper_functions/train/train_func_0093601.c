serverSendReply(name, str)
    char_u	*name;
    char_u	*str;
{
    char_u	*property;
    int		length;
    int		res;
    Display	*dpy = X_DISPLAY;
    Window	win = serverStrToWin(name);

    if (commProperty == None)
    {
	if (SendInit(dpy) < 0)
	    return -2;
    }
    if (!WindowValid(dpy, win))
	return -1;

#ifdef FEAT_MBYTE
    length = STRLEN(p_enc) + STRLEN(str) + 14;
#else
    length = STRLEN(str) + 10;
#endif
    if ((property = (char_u *)alloc((unsigned)length + 30)) != NULL)
    {
#ifdef FEAT_MBYTE
	sprintf((char *)property, "%cn%c-E %s%c-n %s%c-w %x",
			    0, 0, p_enc, 0, str, 0, (unsigned int)commWindow);
#else
	sprintf((char *)property, "%cn%c-n %s%c-w %x",
			    0, 0, str, 0, (unsigned int)commWindow);
#endif

	length += STRLEN(property + length);
	res = AppendPropCarefully(dpy, win, commProperty, property, length + 1);
	vim_free(property);
	return res;
    }
    return -1;
}
