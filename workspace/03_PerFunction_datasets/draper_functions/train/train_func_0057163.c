Draw() {
    IntCoord x0, y0, x1, y1;

    if (!drawn) {
	GetCurrent(x0, y0, x1, y1);
	if (x0 == x1 || y0 == y1) {
	    output->Line(canvas, x0+offx, y0+offy, x1+offx, y1+offy);
	} else {
            output->Rect(canvas, x0+offx, y0+offy, x1+offx, y1+offy);
	}
	drawn = true;
    }
}
