leftPadding() const
{
    if ( d->leftPadding >= 0 )
        return d->leftPadding;
    const KPlotAxis *a = axis( LeftAxis );
    if ( a && a->isVisible() && a->areTickLabelsShown() )
    {
        return !a->label().isEmpty() ? 3 * XPADDING : 2 * XPADDING;
    }
    return XPADDING;
}
