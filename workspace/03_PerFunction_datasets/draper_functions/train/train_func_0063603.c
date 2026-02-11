usesLineWidth() const
{


    return (!isInline()||isHTMLMarquee()) && flowAroundFloats() && style()->width().isAuto() && !isFloating();
}
