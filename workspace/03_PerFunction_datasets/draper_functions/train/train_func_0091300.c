width(const QFontMetrics &fm, const Q3ListView *, int c) const
{
	int x = 0;
	const QPixmap *pix = pixmap(c);
	if(pix)
		x += pix->width();
	else
		x += 16;
	x += 8;
	x += fm.width(text(c));
	x += 8;
	return x;
}
