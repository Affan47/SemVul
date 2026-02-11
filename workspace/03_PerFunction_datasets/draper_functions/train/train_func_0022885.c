utoggle_marking(BW *bw)
{
	if (markv(0) && bw->cursor->b==markb->b && bw->cursor->byte>=markb->byte && bw->cursor->byte<=markk->byte) {

		prm(markb); markb=0;
		prm(markk); markk=0;
		updall();
		marking = 0;
		msgnw(bw->parent, US "Selection cleared.");
		return 0;
	} else if (markk) {

		prm(markb); markb=0;
		prm(markk); markk=0;
		updall();
		marking = 1;
		msgnw(bw->parent, US "Selection started.");
		return umarkb(bw);
	} else if (markb && markb->b==bw->cursor->b) {
		marking = 0;
		if (bw->cursor->byte<markb->byte) {
			pdupown(markb, &markk);
			prm(markb); markb=0;
			pdupown(bw->cursor, &markb);
			markb->xcol = bw->cursor->xcol;
		} else {
			pdupown(bw->cursor, &markk);
			markk->xcol = bw->cursor->xcol;
		}
		updall();
		return 0;
	} else {
		marking = 1;
		msgnw(bw->parent, US "Selection started.");
		return umarkb(bw);
	}
}
