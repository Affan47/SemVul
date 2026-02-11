umwind(BW *bw)
{
	W *msgw;
	if (!errbuf) {
		msgnw(bw->parent, joe_gettext(_("There is no message buffer")));
		return -1;
	}


	msgw = find_window(bw->parent->t, errbuf);

	if (msgw) {

		bw->parent->t->curwin = msgw;
		wshowone(msgw);
		return 0;
	} else {

		msgw = bw->parent;
		get_buffer_in_window(bw, errbuf);
		wshowone(msgw);
		return 0;
	}
}
