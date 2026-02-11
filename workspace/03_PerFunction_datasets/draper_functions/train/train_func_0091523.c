buildTicks(
    const QwtInterval& interval, double stepSize, int maxMinSteps,
    QList<double> ticks[QwtScaleDiv::NTickTypes] ) const
{
    const QwtInterval boundingInterval =
        align( interval, stepSize );

    ticks[QwtScaleDiv::MajorTick] =
        buildMajorTicks( boundingInterval, stepSize );

    if ( maxMinSteps > 0 )
    {
        buildMinorTicks( ticks[QwtScaleDiv::MajorTick], maxMinSteps, stepSize,
            ticks[QwtScaleDiv::MinorTick], ticks[QwtScaleDiv::MediumTick] );
    }

    for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
    {
        ticks[i] = strip( ticks[i], interval );


        for ( int j = 0; j < ticks[i].count(); j++ )
        {
            if ( qwtFuzzyCompare( ticks[i][j], 0.0, stepSize ) == 0 )
                ticks[i][j] = 0.0;
        }
    }
}
