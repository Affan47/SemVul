setAxis( int xAxis, int yAxis )
{
    const QwtPlot *plt = plot();
    if ( !plt )
        return;

    if ( xAxis != d_xAxis || yAxis != d_yAxis )
    {
        d_xAxis = xAxis;
        d_yAxis = yAxis;
    }
}
