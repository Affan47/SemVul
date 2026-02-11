normalized() const
{
    if ( d_minValue > d_maxValue )
    {
        return inverted();
    }
    if ( d_minValue == d_maxValue && d_borderFlags == ExcludeMinimum )
    {
        return inverted();
    }

    return *this;
}
