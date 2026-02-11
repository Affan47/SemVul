inRootBlockContext() const
{
    if (isTableCell() || isFloatingOrPositioned() || hasOverflowClip())
        return false;

    if (isRoot() || isCanvas())
        return true;

    return containingBlock()->inRootBlockContext();
}
