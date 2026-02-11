paintBody(QPainter *painter, const QRect &visibleRect) {
	painter->fillRect(visibleRect, Qt::white);
	QPen pen = painter->pen();
	pen.setColor(QColor(200, 200, 200));
	pen.setCapStyle(Qt::FlatCap);
	painter->setPen(pen);

	int horiAmount = visibleRect.width() - 6;
	int vertiAmount = visibleRect.height() - m_weekCount + 1;


	QDate now = QDate::currentDate();
	if (now >= m_monthBoundingDays.first && now <= m_monthBoundingDays.second)
		painter->fillRect(getDayRect(now), QColor(255, 255, 200));


	for (int i = 1; i < 7; ++i)
		painter->drawLine((i * horiAmount) / 7 + i - 1, 0,
						  (i * horiAmount) / 7 + i - 1, visibleRect.height());


	for (int i = 1; i < m_weekCount; ++i)
		painter->drawLine(0, (i * vertiAmount) / m_weekCount + i - 1,
						  visibleRect.width(), (i * vertiAmount) / m_weekCount + i - 1);


	for (QDate day = m_monthBoundingDays.first; day <= m_monthBoundingDays.second; day = day.addDays(1)) {
		QRect dayRect = getDayRect(day);

		QString text;
		if (day.day() == 1)
            text = QLocale().toString(day, tr("d MMM"));
		else
            text = QLocale().toString(day, tr("d"));

		if (day.month() != firstDate().month())
			pen.setColor(QColor(180, 180, 180));
		else
			pen.setColor(QColor(100, 100, 100));
		painter->setPen(pen);

		painter->drawText(dayRect.adjusted(0, 2, -2, 0), Qt::AlignRight | Qt::AlignTop, text);

	}
}
