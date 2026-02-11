CreateDestClippedRaster(
    const Mapper& mpr, Display& dis, OvRestrictedImage& img,
    const Transformer& tx, XRectangle* bb, IntCoord& dwidth, IntCoord& dheight
) {
    Transformer v(tx);

    float xt, yt;
    mpr.InverseTransform(v, (float)bb->x, (float)bb->y, xt, yt);

    float x0, y0;
    v.transform(0, 0, x0, y0);
    v.translate(-x0, -y0);

    v.transform(xt, yt, xt, yt);

    int xorig = -pround(xt);
    int yorig = -pround(yt);

    dwidth = bb->width;
    dheight = bb->height;

    check_dim(dwidth, dheight);

    return DrawDestTransformedImage(
        dis, img, v, dwidth, dheight, xorig, yorig
    );
}
