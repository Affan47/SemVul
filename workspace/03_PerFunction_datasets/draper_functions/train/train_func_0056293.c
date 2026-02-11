mousePressEvent(QMouseEvent *event)
{
    QStyleOptionComboBox comboOpt;
    comboOpt.initFrom(this);
    const int x0 = QStyle::visualRect(layoutDirection(), rect(),
                                      style()->subControlRect(QStyle::CC_ComboBox, &comboOpt, QStyle::SC_ComboBoxEditField, this)).x();
    const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &comboOpt, this);

    if (event->x() < (x0 + KIconLoader::SizeSmall + frameWidth)) {
        d->m_dragPoint = event->pos();
    } else {
        d->m_dragPoint = QPoint();
    }

    KComboBox::mousePressEvent(event);
}
