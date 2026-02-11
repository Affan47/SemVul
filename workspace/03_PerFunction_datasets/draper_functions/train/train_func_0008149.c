TransformedInfo(
    const Mapper* mpr, IntCoord swidth, IntCoord sheight,
    const Transformer& t, IntCoord* dxmin, IntCoord* dxmax = nil,
    IntCoord* dymin = nil, IntCoord* dymax = nil, IntCoord* pwidth = nil,
    IntCoord* pheight = nil, boolean* rotated = nil
) {
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = sheight;
    float x3 = swidth;
    float y3 = sheight;
    float x4 = swidth;
    float y4 = 0;

    if (mpr) {
        mpr->Transform(t, x1, y1);
        mpr->Transform(t, x2, y2);
        mpr->Transform(t, x3, y3);
        mpr->Transform(t, x4, y4);
    } else {
        t.transform(x1, y1);
        t.transform(x2, y2);
        t.transform(x3, y3);
        t.transform(x4, y4);
    }

    IntCoord xmin, ymin, xmax, ymax;
    xmin = pround(Math::min(x1, x2, x3, x4));
    xmax = pround(Math::max(x1, x2, x3, x4)) - 1;
    ymin = pround(Math::min(y1, y2, y3, y4));
    ymax = pround(Math::max(y1, y2, y3, y4)) - 1;

    if (dxmin) {
        *dxmin = xmin;
    }
    if (dxmax) {
        *dxmax = xmax;
    }
    if (dymin) {
        *dymin = ymin;
    }
    if (dymax) {
        *dymax = ymax;
    }
    if (pwidth) {
        *pwidth = xmax - xmin + 1;
    }
    if (pheight) {
        *pheight = ymax - ymin + 1;
    }
    if (rotated) {
        *rotated = !(
            (pround(x1)==pround(x2) || pround(y1)==pround(y2)) &&
            (pround(x1)==pround(x4) || pround(y1)==pround(y4))
        );
    }
}
