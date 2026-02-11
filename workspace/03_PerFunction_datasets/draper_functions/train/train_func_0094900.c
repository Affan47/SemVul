divideInterval(
    double intervalSize, int numSteps ) const
{
    if ( numSteps <= 0 )
        return 0.0;

    double v = QwtScaleArithmetic::divideEps( intervalSize, numSteps );
    return QwtScaleArithmetic::ceil125( v );
}
