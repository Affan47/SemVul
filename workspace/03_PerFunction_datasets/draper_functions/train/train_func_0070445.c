paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QBrush brush(m_color);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    const qreal sweepLength = m_stopAngle - m_startAngle;
    path.arcMoveTo(boundingRect(), m_startAngle);
    path.arcTo(boundingRect(), m_startAngle, sweepLength);
    QRectF innerRect = boundingRect();
    innerRect.adjust(m_scaleMarkHeight, m_scaleMarkHeight, -m_scaleMarkHeight, -m_scaleMarkHeight);
    path.arcTo(innerRect, m_stopAngle, -sweepLength);
    painter->drawPath(path);
}
