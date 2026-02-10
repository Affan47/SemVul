shrinkBoxesWithNoTextChildren(int topPos, int bottomPos)
{

    for (InlineBox* curr = firstChild(); curr; curr = curr->nextOnLine()) {
        if (curr->object()->isPositioned())
            continue;

        if (curr->isInlineFlowBox())
            static_cast<InlineFlowBox*>(curr)->shrinkBoxesWithNoTextChildren(topPos, bottomPos);
    }


    if (!hasTextDescendant()) {
        if (yPos() < topPos)
            setYPos(topPos);
        if (yPos() + height() > bottomPos)
            setHeight(bottomPos - yPos());
        if (baseline() > height())
            setBaseline(height());
    }
}
