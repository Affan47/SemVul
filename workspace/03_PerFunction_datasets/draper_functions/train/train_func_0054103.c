drawCoordinates(QPaintEvent* event)
{
    if(m_coordinates)
    {
        QPainter p(this);
        p.save();
        p.setPen(m_theme.color(BoardTheme::Frame));
        for(Square square = 0; square < 8; square++)
        {
            QRect rect = coordinateRectVertical(square);
            if(!event->region().intersects(rect))
            {
                continue;
            }
            p.drawText(rect, Qt::AlignCenter, QString("%1").arg(square + 1));
        }
        for(Square square = 0; square < 8; square++)
        {
            QRect rect = coordinateRectHorizontal(square);
            if(!event->region().intersects(rect))
            {
                continue;
            }
            p.drawText(rect, Qt::AlignCenter, QString("%1").arg(QChar('a' + square)));
        }
        p.restore();
    }
}
