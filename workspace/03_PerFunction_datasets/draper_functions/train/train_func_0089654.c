setSamples( const QVector<double> &xData,
    const QVector<double> &yData )
{
    delete d_series;
    d_series = new QwtPointArrayData( xData, yData );
    itemChanged();
}
