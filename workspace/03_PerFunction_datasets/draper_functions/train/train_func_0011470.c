updateSize()
{
	const QPixmap *p;

	if (hasScaledContents() || !_autoresize)
		return;

	p = pixmap();
	if (p && !p->isNull())
	{
		resize(p->width() + frameWidth() * 2, p->height() + frameWidth() * 2);
	}
}
