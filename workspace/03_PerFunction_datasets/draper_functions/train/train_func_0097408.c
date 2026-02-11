pointInHitableShape(boost::int32_t x, boost::int32_t y) const
{
    if (isDynamicMask() && !mouseEnabled()) return false;

    const DisplayObject* mask = getMask();
    if (mask && !mask->pointInShape(x, y)) return false;

    HitableShapeContainerFinder finder(x, y);
    _displayList.visitBackward(finder);
    if (finder.hitFound()) return true;

    return hitTestDrawable(x, y);
}
