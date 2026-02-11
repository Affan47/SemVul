mouseMoveEvent(QMouseEvent *event)
{
    if (!m_frozen || !m_rubberBand)
        return;

    switch (m_Mode) {

    case Create: {

        QRect rect = QRect(m_clickOrigin, event->pos());
        rect.setHeight(rect.height() > 0? abs(rect.width()) : -abs(rect.width()));

        m_rubberBand->setGeometry(rect.normalized());

        restrictRubberBandConstraints();
        break;
    }

    case Move: {

        QPoint relativePosFromClick = event->pos() - m_clickOrigin;

        m_rubberBand->move(m_rubberOrigin + relativePosFromClick);


        restrictRubberBandConstraints();
        break;
    }
    }
}
