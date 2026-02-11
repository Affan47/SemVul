Scale (float sx, float sy, float cx, float cy) {
    float ncx, ncy;

    if (sx != 1 || sy != 1) {
	if (_t == nil) {
	    _t = new Transformer;
	}
	Transformer parents;
	parentXform(parents);
	parents.InvTransform(cx, cy, ncx, ncy);

	if (ncx != 0 || ncy != 0) {
	    _t->Translate(-ncx, -ncy);
	    _t->Scale(sx, sy);
	    _t->Translate(ncx, ncy);
	} else {
	    _t->Scale(sx, sy);
	}
	uncacheParents();
    }
}
