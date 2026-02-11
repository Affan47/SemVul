ViewIntersecting (
    Coord x0, Coord y0, Coord x1, Coord y1
) {
    Selection* s = MakeSelection();
    BoxObj b(x0, y0, x1, y1);
    Graphic* g = GetGraphic()->LastGraphicIntersecting(b);

    if (g != nil) {
        OverlayView* ov = GetOverlayView(g);

        if (ov != nil) {
            s->Append(ov);
        }
    }
    return s;
}
