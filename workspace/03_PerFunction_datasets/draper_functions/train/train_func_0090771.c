getItems() const
    {
        if (!q->model() || !q->firstDate().isValid())
            return QList<CalendarItem>();

        QList<CalendarItem> items = q->model()->getItemsBetween(q->firstDate(), q->firstDate().addDays(m_rangeWidth - 1));

        for (int i = items.count() - 1; i >= 0; i--) {
            const CalendarItem &item = items[i];
            if (item.beginningType() == Date_DateTime && item.endingType() == Date_DateTime)
                items.removeAt(i);
        }
        return items;
    }
