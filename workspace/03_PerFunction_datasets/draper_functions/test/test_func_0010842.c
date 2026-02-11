mouseReleaseEvent(QMouseEvent *event) {
	QWidget::mouseReleaseEvent(event);

    QDate date = d_header->getDate(event->pos().x());
    if (d_header->m_mouseMode == DayRangeHeaderPrivate::MouseMode_Move) {
        if (!d_header->m_pressItemWidget->inMotion()) {

			QMenu menu;
			QAction *modifyAction = menu.addAction(tr("modify"));
			connect(modifyAction, SIGNAL(triggered()), this, SLOT(modifyPressItem()));
			QAction *removeAction = menu.addAction(tr("remove"));
			connect(removeAction, SIGNAL(triggered()), this, SLOT(removePressItem()));
			menu.exec(event->globalPos());
		} else {
            int daysAdded = d_header->m_pressDayInterval.first.daysTo(date);
			if (daysAdded) {
                d_header->m_pressItem.setBeginning(d_header->m_pressItem.beginning().addDays(daysAdded));
                d_header->m_pressItem.setEnding(d_header->m_pressItem.ending().addDays(daysAdded));
			}
            d_header->computeWidgets();
			updateGeometry();
		}
    } else if (d_header->m_mouseMode == DayRangeHeaderPrivate::MouseMode_Creation) {


        CalendarItem item = CalendarItem(QDateTime(d_header->m_pressDayInterval.first, QTime(0, 0)),
                                         QDateTime(d_header->m_pressDayInterval.second.addDays(1), QTime(0, 0)));
		item.setDaily(true);
		model()->addCalendarItem(item);

        d_header->computeWidgets();
		updateGeometry();
	}

    d_header->m_mouseMode = DayRangeHeaderPrivate::MouseMode_None;
}
