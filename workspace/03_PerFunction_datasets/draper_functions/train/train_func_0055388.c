serverReadReply(dpy, win, str, localLoop)
    Display	*dpy;
    Window	win;
    char_u	**str;
    int		localLoop;
{
    int		len;
    char_u	*s;
    struct	ServerReply *p;

    ServerWait(dpy, win, WaitForReply, &win, localLoop, -1);

    if ((p = ServerReplyFind(win, SROP_Find)) != NULL && p->strings.ga_len > 0)
    {
	*str = vim_strsave(p->strings.ga_data);
	len = STRLEN(*str) + 1;
	if (len < p->strings.ga_len)
	{
	    s = (char_u *) p->strings.ga_data;
	    mch_memmove(s, s + len, p->strings.ga_len - len);
	    p->strings.ga_len -= len;
	}
	else
	{

	    ga_clear(&p->strings);
	    ServerReplyFind(win, SROP_Delete);
	}
	return 0;
    }
    return -1;
}
