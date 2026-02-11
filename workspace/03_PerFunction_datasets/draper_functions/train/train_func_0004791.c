ui_textmouse(struct ui_textdata *d, int x, int y)
{
    if (y > d->y && y < d->y + xtextheight(uih->image, uih->font) && x > d->x) {
	int w = 0;
	int i;
	int xp = d->x;
	for (i = 0; i < d->ndisplayed + 1 && xp - w / 2 < x; i++) {
	    w = xtextcharw(uih->image, uih->font, d->text[i + d->start]);
	    xp += w;
	}
	d->cursor = i + d->start - 1;
	if (d->cursor < 0)
	    d->cursor = 0;
	d->clear = 0;
	ui_updatetext(d);
	uih->display = 1;
    }
}
