paint(Graphics &g, const YRect &) {
    int d((fPressed || fArmed) ? 1 : 0);
    int x(0), y(0), w(width()), h(height());

    if (w > 1 && h > 1) {
        YSurface surface(getSurface());
        g.setColor(surface.color);

        if (wmLook == lookMetal) {
            g.drawBorderM(x, y, w - 1, h - 1, !d);
            d = 0; x += 2; y += 2; w -= 4; h -= 4;
        } else if (wmLook == lookGtk) {
            g.drawBorderG(x, y, w - 1, h - 1, !d);
            x += 1 + d; y += 1 + d; w -= 3; h -= 3;
	} else if (wmLook == lookFlat){
	    d = 0;
        } else {
            g.drawBorderW(x, y, w - 1, h - 1, !d);
            x += 1 + d; y += 1 + d; w -= 3; h -= 3;
        }

        paint(g, d, YRect(x, y, w, h));

        if (wmLook != lookFlat) {
            paintFocus(g, YRect(x, y, w, h));
        }
    }
}
