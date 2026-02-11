aapolygonColor(SDL_Surface * dst, Sint16 * vx, Sint16 * vy, int n, Uint32 color)
{
    int result;
    int i;
    Sint16 *x1, *y1, *x2, *y2;


    if (n < 3) {
        return (-1);
    }


    x1 = x2 = vx;
    y1 = y2 = vy;
    x2++;
    y2++;


    result = 0;
    for (i = 1; i < n; i++) {
        result |= aalineColorInt(dst, *x1, *y1, *x2, *y2, color, 0);
        x1 = x2;
        y1 = y2;
        x2++;
        y2++;
    }
    result |= aalineColorInt(dst, *x1, *y1, *vx, *vy, color, 0);

    return (result);
}
