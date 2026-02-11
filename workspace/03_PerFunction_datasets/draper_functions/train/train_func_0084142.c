paintEvent( QPaintEvent *e )
{
    const QRect cr = contentsRect();

    QPainter painter( this );
    painter.setClipRegion( e->region() );

    if ( d_data->isDown )
    {
        qDrawWinButton( &painter, 0, 0, width(), height(),
            palette(), true );
    }

    painter.save();

    if ( d_data->isDown )
    {
        const QSize shiftSize = buttonShift( this );
        painter.translate( shiftSize.width(), shiftSize.height() );
    }

    painter.setClipRect( cr );

    drawContents( &painter );

    if ( !d_data->identifier.isNull() )
    {
        QRect identRect = cr;
        identRect.setX( identRect.x() + margin() );
        if ( d_data->itemMode != QwtLegend::ReadOnlyItem )
            identRect.setX( identRect.x() + ButtonFrame );

        identRect.setSize( d_data->identifier.size() );
        identRect.moveCenter( QPoint( identRect.center().x(), cr.center().y() ) );

        painter.drawPixmap( identRect, d_data->identifier );
    }

    painter.restore();
}
