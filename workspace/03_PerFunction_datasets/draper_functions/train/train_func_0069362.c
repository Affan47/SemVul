coordinateRectHorizontal(Square square)
{
    Q_ASSERT(m_coordinates);
    int y = isFlipped() ? 7 - square % 8 : square % 8;
    return QRect(CoordinateSize + (y * (m_theme.size().width())) + (m_theme.size().width() - CoordinateSize) / 2,
                 8 * m_theme.size().height(),
                 CoordinateSize, CoordinateSize);
}
