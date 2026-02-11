drawSeries(
    QwtPlotAbstractSeriesItem *seriesItem, int from, int to )
{
    if ( seriesItem == NULL || seriesItem->plot() == NULL )
        return;

    QwtPlotCanvas *canvas = seriesItem->plot()->canvas();
    const QRect canvasRect = canvas->contentsRect();

    const bool hasBackingStore =
        canvas->testPaintAttribute( QwtPlotCanvas::BackingStore )
        && canvas->backingStore() && !canvas->backingStore()->isNull();

    if ( hasBackingStore )
    {
        QPainter painter( const_cast<QPixmap *>( canvas->backingStore() ) );
        painter.translate( -canvasRect.x(), -canvasRect.y() );

        if ( d_data->hasClipping )
            painter.setClipRegion( d_data->clipRegion );

        renderItem( &painter, canvasRect, seriesItem, from, to );

        if ( testAttribute( QwtPlotDirectPainter::FullRepaint ) )
        {
            canvas->repaint();
            return;
        }
    }

    bool immediatePaint = true;
    if ( !canvas->testAttribute( Qt::WA_WState_InPaintEvent ) &&
        !canvas->testAttribute( Qt::WA_PaintOutsidePaintEvent ) )
    {
        immediatePaint = false;
    }

    if ( immediatePaint )
    {
        QwtPlotCanvas *canvas = seriesItem->plot()->canvas();
        if ( !d_data->painter.isActive() )
        {
            reset();

            d_data->painter.begin( canvas );
            canvas->installEventFilter( this );
        }

        if ( d_data->hasClipping )
        {
            d_data->painter.setClipRegion(
                QRegion( canvasRect ) & d_data->clipRegion );
        }
        else
        {
            if ( !d_data->painter.hasClipping() )
                d_data->painter.setClipRect( canvasRect );
        }

        renderItem( &d_data->painter, canvasRect, seriesItem, from, to );

        if ( d_data->attributes & QwtPlotDirectPainter::AtomicPainter )
        {
            reset();
        }
        else
        {
            if ( d_data->hasClipping )
                d_data->painter.setClipping( false );
        }
    }
    else
    {
        reset();

        d_data->seriesItem = seriesItem;
        d_data->from = from;
        d_data->to = to;

        QRegion clipRegion = canvasRect;
        if ( d_data->hasClipping )
            clipRegion &= d_data->clipRegion;

        canvas->installEventFilter( this );
        canvas->repaint(clipRegion);
        canvas->removeEventFilter( this );

        d_data->seriesItem = NULL;
    }
}
