smartSpacing(QStyle::PixelMetric pm) const
    {
        QObject *parent = q->parent();
        if (!parent) {
            return -1;
        } else if (parent->isWidgetType()) {
            QWidget *pw = static_cast<QWidget *>(parent);
            return pw->style()->pixelMetric(pm, 0, pw);
        } else {
            return static_cast<QLayout *>(parent)->spacing();
        }
    }
