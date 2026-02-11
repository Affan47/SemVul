drawSquares(QPaintEvent* event)
{
    QPainter p(this);
    for(Square square = 0; square < 64; square++)
    {
        QRect rect = squareRect(square);
        if(!event->region().intersects(rect))
        {
            continue;
        }
        int coord =  m_coordinates ? CoordinateSize : 0;
        int x = isFlipped() ? 7 - square % 8 : square % 8;
        int y = isFlipped() ? square / 8 : 7 - square / 8;
        QPoint pos(coord + x * m_theme.size().width(), y * m_theme.size().height());
        p.drawPixmap(pos, m_theme.square((x + y) % 2));
    }
}
