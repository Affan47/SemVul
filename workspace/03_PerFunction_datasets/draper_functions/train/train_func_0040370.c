canAccommodateEllipsisBox(bool ltr, int blockEdge, int ellipsisWidth)
{

    if (!m_object || !m_object->isReplaced())
        return true;

    QRect boxRect(m_x, 0, m_width, 10);
    QRect ellipsisRect(ltr ? blockEdge - ellipsisWidth : blockEdge, 0, ellipsisWidth, 10);
    return !(boxRect.intersects(ellipsisRect));
}
