calcReplacedWidthUsing(WidthType widthType) const
{
    Length w;
    if (widthType == Width)
        w = style()->width();
    else if (widthType == MinWidth)
        w = style()->minWidth();
    else
        w = style()->maxWidth();

    switch (w.type()) {
    case Fixed:
        return calcContentWidth(w.value());
    case Percent:
    {
        const int cw = containingBlockWidth();
        if (cw > 0) {
            int result = calcContentWidth(w.minWidth(cw));
            return result;
        }
    }

    default:
        return intrinsicWidth();
    }
}
