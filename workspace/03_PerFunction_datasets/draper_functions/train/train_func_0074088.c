drawTick( QPainter *painter, double value, double len ) const
{
    if ( len <= 0 )
        return;

    const bool roundingAlignment = QwtPainter::roundingAlignment( painter );

    QPointF pos = d_data->pos;

    double tval = scaleMap().transform( value );
    if ( roundingAlignment )
        tval = qRound( tval );

    const int pw = penWidth();
    int a = 0;
    if ( pw > 1 && roundingAlignment )
        a = 1;

    switch ( alignment() )
    {
        case LeftScale:
        {
            double x1 = pos.x() + a;
            double x2 = pos.x() + a - pw - len;
            if ( roundingAlignment )
            {
                x1 = qRound( x1 );
                x2 = qRound( x2 );
            }

            QwtPainter::drawLine( painter, x1, tval, x2, tval );
            break;
        }

        case RightScale:
        {
            double x1 = pos.x();
            double x2 = pos.x() + pw + len;
            if ( roundingAlignment )
            {
                x1 = qRound( x1 );
                x2 = qRound( x2 );
            }

            QwtPainter::drawLine( painter, x1, tval, x2, tval );
            break;
        }

        case BottomScale:
        {
            double y1 = pos.y();
            double y2 = pos.y() + pw + len;
            if ( roundingAlignment )
            {
                y1 = qRound( y1 );
                y2 = qRound( y2 );
            }

            QwtPainter::drawLine( painter, tval, y1, tval, y2 );
            break;
        }

        case TopScale:
        {
            double y1 = pos.y() + a;
            double y2 = pos.y() - pw - len + a;
            if ( roundingAlignment )
            {
                y1 = qRound( y1 );
                y2 = qRound( y2 );
            }

            QwtPainter::drawLine( painter, tval, y1, tval, y2 );
            break;
        }
    }
}
