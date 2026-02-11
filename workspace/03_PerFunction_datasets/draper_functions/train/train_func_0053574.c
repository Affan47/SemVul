getBottomCoord(int My, YFrameWindow **w, int count)
{
    int i, n;

    if ((y() + height()) > My)
        return y() + height();

    for (i = y() + height() + 2; i < My; i++) {
        for (n = 0; n < count; n++) {
            if (    (this != w[n])
                 && (i == w[n]->y())
                 && ( x()            < (w[n]->x() + w[n]->width()))
                 && ((x() + width()) > (w[n]->x())) ) {
                return i;
            }
        }
    }

    return My;
}
