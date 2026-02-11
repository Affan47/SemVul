parserrb(B *b)
{
	BW *bw;
	int n;
	errbuf = b;
	freeall();
	n = parserr(b);
	bw = find_a_good_bw(b);
	if (n)
		joe_snprintf_1(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("%d messages found")), n);
	else
		joe_snprintf_0(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("No messages found")));
	msgnw(bw->parent, msgbuf);
	return 0;
}
