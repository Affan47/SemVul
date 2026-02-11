pointInShape(boost::int32_t x, boost::int32_t y) const
{
    ShapeContainerFinder finder(x, y);
    _displayList.visitBackward(finder);
    if ( finder.hitFound() ) return true;
    return hitTestDrawable(x, y);
}
