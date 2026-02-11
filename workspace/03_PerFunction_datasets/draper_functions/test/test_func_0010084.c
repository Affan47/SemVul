isSelfCollapsingBlock() const
{


    if (m_height > 0 ||
        isTable() || (borderBottom() + paddingBottom() + borderTop() + paddingTop()) != 0 ||
        style()->minHeight().isPositive())
        return false;

    bool hasAutoHeight = style()->height().isAuto();
    if (style()->height().isPercent() && !style()->htmlHacks()) {
        hasAutoHeight = true;
        for (RenderBlock* cb = containingBlock(); !cb->isCanvas(); cb = cb->containingBlock()) {
            if (cb->style()->height().isFixed() || cb->isTableCell())
                hasAutoHeight = false;
        }
    }


    if (hasAutoHeight || ((style()->height().isFixed() || style()->height().isPercent()) && style()->height().isZero())) {


        if (childrenInline())
            return !firstLineBox();


        for (RenderObject* child = firstChild(); child; child = child->nextSibling()) {
            if (child->isFloatingOrPositioned())
                continue;
            if (!child->isSelfCollapsingBlock())
                return false;
        }
        return true;
    }
    return false;
}
