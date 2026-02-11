dosave(BW *bw, struct savereq *req, int *notify)
{
	if (req->block_save)
	{
		if (notify)
			*notify = 1;
		if (markv(1)) {
			if (square) {
				int fl;
				int ret = 0;
				B *tmp = pextrect(markb,
						  markk->line - markb->line + 1,
						  markk->xcol);

				if ((fl = bsave(tmp->bof, req->name, tmp->eof->byte, 0)) != 0) {
					msgnw(bw->parent, joe_gettext(msgs[-fl]));
					ret = -1;
				}
				brm(tmp);
				if (!ret) {
					joe_snprintf_1(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("Block written to file %s")), req->name);
					msgnw(bw->parent, msgbuf);
				}
				if (lightoff)
					unmark(bw);
				vsrm(req->name);
				return ret;
			} else {
				int fl;
				int ret = 0;

				if ((fl = bsave(markb, req->name, markk->byte - markb->byte, 0)) != 0) {
					msgnw(bw->parent, joe_gettext(msgs[-fl]));
					ret = -1;
				}
				if (!ret) {
					joe_snprintf_1(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("Block written to file %s")), req->name);
					msgnw(bw->parent, msgbuf);
				}
				if (lightoff)
					unmark(bw);
					vsrm(req->name);
				return ret;
			}
		} else {
			vsrm(req->name);
			msgnw(bw->parent, joe_gettext(_("No block")));
			return -1;
		}
	}
	else
	{
		if (backup(bw)) {
			return saver(bw, 0, req, notify);
		} else {
			return saver(bw, YES_CODE, req, notify);
		}
	}
}
