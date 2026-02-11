computeWidgets() {

        foreach (QObject *object, q->children()) {
            DayWidget *widget = qobject_cast<DayWidget*>(object);
            if (widget)
                delete widget;
        }

        m_maxDepth = -1;


        QList<CalendarItem> items = getItems();
        if (!items.count())
            return;

        qSort(items.begin(), items.end(), calendarItemLessThan);

        m_maxDepth = 0;

        DayStore store;
        for (int i = 0; i < items.count(); i++) {
            int depth = store.store(items[i]);
            if (depth > m_maxDepth)
                m_maxDepth = depth;
            computeWidget(items[i], depth);
        }
    }
