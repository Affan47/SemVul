SetIndicator(const bool b, const int t, const bool c)
{
    if (mShowIndicator != b || mIndicatorType != t || mHideColor != c)
    {
        mShowIndicator = b;
        mIndicatorType = t;
        mHideColor = c;
        update(boundingRect());
    }
}
