ubegin_marking(BW *bw)
{
	if (marking)

		return 0;
	else if (markv(0) && bw->cursor->b==markb->b) {

		if (bw->cursor->byte==markb->byte) {
			pset(markb,markk);
			prm(markk); markk=0;
			marking = 1;
			return 0;
		} else if(bw->cursor->byte==markk->byte) {
			prm(markk); markk=0;
			marking = 1;
			return 0;
		}
	}

	prm(markb); markb=0;
	prm(markk); markk=0;
	updall();
	marking = 1;
	return umarkb(bw);
}
