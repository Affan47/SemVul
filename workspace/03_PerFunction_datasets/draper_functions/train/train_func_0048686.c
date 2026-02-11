markAllDescendantsWithFloatsForLayout(RenderObject* floatToRemove)
{
    dirtyFormattingContext(false);
    setChildNeedsLayout(true);

    if (floatToRemove)
        removeFloatingObject(floatToRemove);


    if (!childrenInline()) {
        for (RenderObject* child = firstChild(); child; child = child->nextSibling()) {
            if (isBlockFlow() && !child->isFloatingOrPositioned() &&
                ((floatToRemove ? child->containsFloat(floatToRemove) : child->hasFloats()) || child->usesLineWidth()))
                child->markAllDescendantsWithFloatsForLayout(floatToRemove);
        }
    }
}
