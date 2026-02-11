doscratch(BW *bw, unsigned char *s, void *obj, int *notify)
{
	int ret = 0;
	int er;
	void *object;
	W *w;
	B *b;

	if (notify) {
		*notify = 1;
	}

	b = bfind_scratch(s);
	er = berror;
	if (bw->b->count == 1 && (bw->b->changed || bw->b->name)) {
		if (orphan) {
			orphit(bw);
		} else {
			if (uduptw(bw)) {
				brm(b);
				return -1;
			}
			bw = (BW *) maint->curwin->object;
		}
	}
	if (er) {
		msgnwt(bw->parent, joe_gettext(msgs[-er]));
		if (er != -1) {
			ret = -1;
		}
	}
	object = bw->object;
	w = bw->parent;
	bwrm(bw);
	w->object = (void *) (bw = bwmk(w, b, 0));
	wredraw(bw->parent);
	bw->object = object;
	vsrm(s);
	if (er == -1 && bw->o.mnew) {
		exmacro(bw->o.mnew,1);
	}
	if (er == 0 && bw->o.mold) {
		exmacro(bw->o.mold,1);
	}
	return ret;
}
