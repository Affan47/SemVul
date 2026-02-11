event(QEvent *ev)
{
    switch (ev->type()) {
        case QEvent::HoverMove:
        {
            QHoverEvent *e = static_cast<QHoverEvent *>(ev);
            const int row = e->pos().y() * d->m_numWeekRows / height();
            int col;
            if ( layoutDirection() == Qt::RightToLeft ) {
                col = d->m_numDayColumns - ( e->pos().x() * d->m_numDayColumns / width() ) - 1;
            } else {
                col = e->pos().x() * d->m_numDayColumns / width();
            }

            const int pos = row < 1 ? -1 : (d->m_numDayColumns * (row - 1)) + col;

            if (pos != d->m_hoveredPos) {
                d->m_hoveredPos = pos;
                update();
            }
            break;
        }
        case QEvent::HoverLeave:
            if (d->m_hoveredPos != -1) {
                d->m_hoveredPos = -1;
                update();
            }
            break;
        default:
            break;
    }
    return QWidget::event(ev);
}
