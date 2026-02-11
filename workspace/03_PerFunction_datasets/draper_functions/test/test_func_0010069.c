paintEvent(QPaintEvent *) {

	QPainter painter(this);
	painter.fillRect(rect(), QColor(220, 220, 255));


	QPen pen = painter.pen();
	pen.setColor(QColor(200, 200, 255));
	painter.setPen(pen);
	painter.drawLine(0, rect().bottom(), rect().right(), rect().bottom());


	pen.setColor(QColor(150, 150, 255));
	painter.setPen(pen);

	int containWidth = rect().width();
	for (int i = 0; i < 7; ++i) {
        QRect r(QPoint((i * containWidth) / 7, 0), QPoint(((i + 1) * containWidth) / 7 - 1 + 2, rect().height()));
        painter.drawText(r, Qt::AlignHCenter | Qt::AlignTop, QLocale().toString(QDate(2012, 05, 07 + i), "ddd"));
	}
}
