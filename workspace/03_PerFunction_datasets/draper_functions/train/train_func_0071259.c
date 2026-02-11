handleFloatingChild(RenderObject* child, const MarginInfo& marginInfo, bool& handled)
{
    if (child->isFloating()) {
        handled = true;
        insertFloatingObject(child);
        adjustFloatingBlock(marginInfo);
        return child->nextSibling();
    }
    return 0;
}
