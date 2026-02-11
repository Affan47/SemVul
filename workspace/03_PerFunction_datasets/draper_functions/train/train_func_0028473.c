set_shape(client_t *c)
{
    int n, order;
    XRectangle temp, *rects;

    rects = XShapeGetRectangles(dpy, c->win, ShapeBounding, &n, &order);

    if (n > 1) {
        XShapeCombineShape(dpy, c->frame, ShapeBounding,
            0, frame_height(c), c->win, ShapeBounding, ShapeSet);
        temp.x = -BW(c);
        temp.y = -BW(c);
        temp.width = c->geom.w + 2*BW(c);
        temp.height = frame_height(c) + BW(c);
        XShapeCombineRectangles(dpy, c->frame, ShapeBounding,
            0, 0, &temp, 1, ShapeUnion, YXBanded);
        temp.x = 0;
        temp.y = 0;
        temp.width = c->geom.w;
        temp.height = frame_height(c) - BW(c);
        XShapeCombineRectangles(dpy, c->frame, ShapeClip,
            0, frame_height(c), &temp, 1, ShapeUnion, YXBanded);
        c->shaped = 1;
    } else if (c->shaped) {

        temp.x = -BW(c);
        temp.y = -BW(c);
        temp.width = c->geom.w + 2*BW(c);
        temp.height = c->geom.h + frame_height(c) + 2*BW(c);
        XShapeCombineRectangles(dpy, c->frame, ShapeBounding,
            0, 0, &temp, 1, ShapeSet, YXBanded);
    }

    XFree(rects);
}
