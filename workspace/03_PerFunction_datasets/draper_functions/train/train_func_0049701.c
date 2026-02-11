isPointInsideSelection(int x, int y, const Selection &sel) const
{
    SelectionState selstate = selectionState();
    if (selstate == SelectionInside) return true;
    if (selstate == SelectionNone || !element()) return false;
    return element()->isPointInsideSelection(x, y, sel);
}
