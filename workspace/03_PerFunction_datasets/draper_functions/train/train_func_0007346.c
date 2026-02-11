drawLeft(bool draw)
{
	QColor col(draw ? Qt::black : Qt::white);
	if (!left_.enabled)
		col = QColor(Qt::lightGray);
	drawLine(col, m + l, m + l + 2, m + l, h - m - l - 1);
}
