setYAxis( int axis )
{
    if ( axis == QwtPlot::yLeft || axis == QwtPlot::yRight ||
         axis == QwtPlot::yLeft1 || axis == QwtPlot::yRight1 ||
         axis == QwtPlot::yLeft2 || axis == QwtPlot::yRight2 ||
         axis == QwtPlot::yLeft3 || axis == QwtPlot::yRight3 )
    {
        d_data->yAxis = axis;
        itemChanged();
    }
}
