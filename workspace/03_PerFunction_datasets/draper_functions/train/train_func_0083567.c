bwfllwh(BW *w)
{

	if (w->top->byte%16) {
		pbkwd(w->top,w->top->byte%16);
	}


	if (w->cursor->byte < w->top->byte) {
		long new_top = w->cursor->byte/16;
		if (mid) {
			if (new_top >= w->h / 2)
				new_top -= w->h / 2;
			else
				new_top = 0;
		}
		if (w->top->byte/16 - new_top < w->h)
			nscrldn(w->t->t, w->y, w->y + w->h, (int) (w->top->byte/16 - new_top));
		else
			msetI(w->t->t->updtab + w->y, 1, w->h);
		pgoto(w->top,new_top*16);
	}


	if (w->cursor->byte >= w->top->byte+(w->h*16)) {
		long new_top;
		if (mid) {
			new_top = w->cursor->byte/16 - w->h / 2;
		} else {
			new_top = w->cursor->byte/16 - (w->h - 1);
		}
		if (new_top - w->top->byte/16 < w->h)
			nscrlup(w->t->t, w->y, w->y + w->h, (int) (new_top - w->top->byte/16));
		else {
			msetI(w->t->t->updtab + w->y, 1, w->h);
		}
		pgoto(w->top, new_top*16);
	}


	if (w->cursor->byte%16+60 < w->offset) {
		w->offset = w->cursor->byte%16+60;
		msetI(w->t->t->updtab + w->y, 1, w->h);
	} else if (w->cursor->byte%16+60 >= w->offset + w->w) {
		w->offset = w->cursor->byte%16+60 - (w->w - 1);
		msetI(w->t->t->updtab + w->y, 1, w->h);
	}
}
