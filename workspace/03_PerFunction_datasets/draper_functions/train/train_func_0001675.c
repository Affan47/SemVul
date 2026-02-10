getWidgetsByDate(const QDate &dayDate) const
{
	QList<CalendarItemWidget*> list;
	foreach (QObject *obj, children()) {
		CalendarItemWidget *widget = qobject_cast<CalendarItemWidget*>(obj);
		if (widget && widget->beginDateTime().date() == dayDate)
			list << widget;
	}
	return list;
}
