udefm2down(BW *xx)
{
	BW *bw;
	if (utomouse(xx))
		return -1;
	if (maint->curwin->watom->what & TYPEMENU) {
		return maint->curwin->watom->rtn((MENU *)maint->curwin->object);
	}
	if ((maint->curwin->watom->what & (TYPEPW | TYPETW)) == 0)
		return 0;
	bw = (BW *)maint->curwin->object;

	u_goto_prev(bw); anchor = bw->cursor->byte; umarkb(bw); markb->xcol = piscol(markb);
	u_goto_next(bw); anchorn = bw->cursor->byte; umarkk(bw); markk->xcol = piscol(markk);
	reversed = 0;
	bw->cursor->xcol = piscol(bw->cursor);
	selecting = 1;
	return 0;
}
