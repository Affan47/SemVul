crossesPageBreak(int t, int b) const
{
    RenderObject* cb = container();
    if (cb)
        return cb->crossesPageBreak(yPos()+t, yPos()+b);
    else
        return false;
}
