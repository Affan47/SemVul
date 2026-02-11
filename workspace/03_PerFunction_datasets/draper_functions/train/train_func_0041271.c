color2pixmap(QColor c)
{
	QPixmap pix(16, 16);
	QPainter p(&pix);

	p.fillRect(0, 0, pix.width(), pix.height(), QBrush(c));
	p.setPen( QColor(0, 0, 0) );
	p.drawRect(0, 0, pix.width(), pix.height());
	p.end();

	return pix;
}
