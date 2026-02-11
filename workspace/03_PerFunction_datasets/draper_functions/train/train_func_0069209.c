get_text_height(QPainter *dp, QString &s)
{
	text_line = dp->fontMetrics().height();
	return text_line * (1 + s.count('\n'));
}
