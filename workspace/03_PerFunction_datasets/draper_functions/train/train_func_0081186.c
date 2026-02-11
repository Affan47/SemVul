paddingTop() const
{
    int w = 0;
    Length padding = m_style->paddingTop();
    if (padding.isPercent())
        w = containingBlock()->contentWidth();
    w = padding.minWidth(w);
    if ( isTableCell() && padding.isAuto() )
        w = static_cast<const RenderTableCell *>(this)->table()->cellPadding();
    return w;
}
