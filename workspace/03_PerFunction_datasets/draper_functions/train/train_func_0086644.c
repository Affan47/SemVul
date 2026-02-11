setAlignment(Qt::Alignment a)
{
    if (m_alignment != a) {
        m_alignment = a;
        emit alignmentChanged(reinterpret_cast<QGraphicsLayoutItem*>(parent()), m_alignment);
    }
}
