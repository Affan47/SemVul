paintEvent(QPaintEvent *)
{
	QPainter p;
	QFontMetrics m(font_);

	p.begin(this);
	p.setFont(font_);
	p.drawRect(0, 0, width() - 1, height() - 1);
	p.drawText(5, 3 + m.ascent(), text_);
	p.end();
}
