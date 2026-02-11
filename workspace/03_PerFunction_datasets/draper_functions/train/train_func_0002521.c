rescale()
{
    QwtPlot *plt = plot();
    if ( !plt )
        return;

    const QRectF &rect = d_data->zoomStack[d_data->zoomRectIndex];
    if ( rect != scaleRect() )
    {
        const bool doReplot = plt->autoReplot();
        plt->setAutoReplot( false );

        double x1 = rect.left();
        double x2 = rect.right();
        if ( plt->axisScaleDiv( xAxis() )->lowerBound() >
            plt->axisScaleDiv( xAxis() )->upperBound() )
        {
            qSwap( x1, x2 );
        }

        plt->setAxisScale( xAxis(), x1, x2 );

        double y1 = rect.top();
        double y2 = rect.bottom();
        if ( plt->axisScaleDiv( yAxis() )->lowerBound() >
            plt->axisScaleDiv( yAxis() )->upperBound() )
        {
            qSwap( y1, y2 );
        }
        plt->setAxisScale( yAxis(), y1, y2 );

        plt->setAutoReplot( doReplot );

        plt->replot();
    }
}
