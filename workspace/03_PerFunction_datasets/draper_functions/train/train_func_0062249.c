enclosingPositionedRect (RenderObject *n)
{
    RenderObject *enclosingParent =  n->containingBlock();
    QRect rect(0,0,0,0);
    if (enclosingParent) {
        int ox, oy;
        enclosingParent->absolutePosition(ox, oy);
        if (!enclosingParent->hasOverflowClip()) {
            ox += enclosingParent->overflowLeft();
            oy += enclosingParent->overflowTop();
        }
        rect.setX(ox);
        rect.setY(oy);
        rect.setWidth(enclosingParent->effectiveWidth());
        rect.setHeight(enclosingParent->effectiveHeight());
    }
    return rect;
}
