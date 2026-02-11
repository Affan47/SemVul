online2(x0, y0, x1, y1)
    int x0, y0, x1, y1;
{
    int dx = x0 - x1, dy = y0 - y1;


    return((boolean)(!dy || !dx || (dy == dx) || (dy + dx == 0)));
}
