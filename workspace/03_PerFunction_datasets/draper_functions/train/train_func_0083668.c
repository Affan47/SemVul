paintEvent(QPaintEvent* event)
{
	QTableView::paintEvent(event);

	if(!mDropIndicator.size().isEmpty())
	{
		QPalette p = QApplication::palette();
		QPen pen(p.color(QPalette::Highlight), 3, Qt::DotLine);
		QPainter painter(viewport());
		painter.setPen(pen);

		mDropIndicator.translate(0, -1);
		mDropIndicator.setLeft(0);
		mDropIndicator.setRight(viewport()->rect().size().width());

		painter.drawLine(mDropIndicator.topLeft(), mDropIndicator.topRight());
	}
}
