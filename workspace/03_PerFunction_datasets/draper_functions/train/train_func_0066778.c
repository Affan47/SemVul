rectangleColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
    int result;
    Sint16 w, h, xtmp, ytmp;


    if (x1 > x2) {
        xtmp = x1;
        x1 = x2;
        x2 = xtmp;
    }


    if (y1 > y2) {
        ytmp = y1;
        y1 = y2;
        y2 = ytmp;
    }


    w = x2 - x1;
    h = y2 - y1;


    if ((w < 0) || (h < 0)) {
        return (0);
    }


    if (x1 == x2) {
        if (y1 == y2) {
            return (pixelColor(dst, x1, y1, color));
        } else {
            return (vlineColor(dst, x1, y1, y2, color));
        }
    } else {
        if (y1 == y2) {
            return (hlineColor(dst, x1, x2, y1, color));
        }
    }


    result = 0;
    result |= vlineColor(dst, x1, y1, y2, color);
    result |= vlineColor(dst, x2, y1, y2, color);
    result |= hlineColor(dst, x1, x2, y1, color);
    result |= hlineColor(dst, x1, x2, y2, color);

    return (result);

}
