getLastWidgetBottom() const
    {
        int maxBottom = -1;
        foreach (QObject *obj, q->children()) {
            DayWidget *widget = qobject_cast<DayWidget*>(obj);
            if (!widget)
                continue;
            int bottom = widget->y() + widget->height();
            if (widget && bottom > maxBottom)
                maxBottom = bottom;
        }
        return maxBottom;
    }
