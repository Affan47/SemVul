x() const
{
    if (renderer()) {
        int x = 0;
        int y = 0;
        renderer()->absolutePosition(x,y);
        return x;
    }
    return 0;
}
