dogomark(BW *bw, int c, void *object, int *notify)
{
	if (notify)
		*notify = 1;
	if (c >= '0' && c <= ':')
		if (bw->b->marks[c - '0']) {
			pset(bw->cursor, bw->b->marks[c - '0']);
			bw->cursor->xcol = piscol(bw->cursor);
			return 0;
		} else {
			joe_snprintf_1(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("Mark %d not set")), c - '0');
			msgnw(bw->parent, msgbuf);
			return -1;
	} else {
		nungetc(c);
		return -1;
	}
}
