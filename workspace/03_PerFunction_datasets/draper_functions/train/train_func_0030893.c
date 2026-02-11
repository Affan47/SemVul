qwtIsVSampleInside( const QwtIntervalSample &sample,
    double xMin, double xMax, double yMin, double yMax )
{
    const double x = sample.value;
    const double y1 = sample.interval.minValue();
    const double y2 = sample.interval.maxValue();

    const bool isOffScreen = ( x < xMin ) || ( x > xMax )
        || ( y1 < yMin && y2 < yMin ) || ( y1 > yMax && y2 > yMax );

    return !isOffScreen;
}
