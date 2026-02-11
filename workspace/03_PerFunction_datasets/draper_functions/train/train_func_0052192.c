mousePressEvent(QMouseEvent *event) {

    if (event->pos().x() < 60 || event->pos().y() < d_header->getScaleHeight()) {
		QWidget::mousePressEvent(event);
		return;
	}

    d_header->m_pressDate = d_header->getDate(event->pos().x());
    d_header->m_previousDate = d_header->m_pressDate;
    d_header->m_pressPos = event->pos();


    d_header->m_pressItemWidget = qobject_cast<DayWidget*>(childAt(event->pos()));
    if (d_header->m_pressItemWidget) {
        d_header->m_pressItem = model()->getItemByUid(d_header->m_pressItemWidget->uid());
        d_header->m_pressDayInterval = getIntersectDayRange(d_header->m_pressItem.beginning(), d_header->m_pressItem.ending());
        d_header->m_mouseMode = DayRangeHeaderPrivate::MouseMode_Move;
	} else {
        d_header->m_mouseMode = DayRangeHeaderPrivate::MouseMode_Creation;

        d_header->m_pressDayInterval.first = d_header->m_pressDate;
        d_header->m_pressDayInterval.second = d_header->m_pressDate;
		update();
	}
}
