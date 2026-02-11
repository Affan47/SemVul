CreateStretchManip (
    Viewer* v, Event& e, Transformer* rel, Tool* tool
) {
    Coord l, b, r, t, tmp;
    DragConstraint dc = HorizOrVert;

    v->Constrain(e.x, e.y);
    GetGraphic()->GetBox(l, b, r, t);
    boolean horizCtr = e.x > (2*l + r)/3 && e.x < (l + 2*r)/3;
    boolean vertCtr  = e.y > (2*b + t)/3 && e.y < (b + 2*t)/3;

    if (e.x < (l + r)/2) {
        tmp = r;
        r = l;
        l = tmp;
    }
    if (e.y < (b + t)/2) {
        tmp = t;
        t = b;
        b = tmp;
    }
    if (horizCtr && !vertCtr) {
        dc = XFixed;
    } else if (!horizCtr && vertCtr) {
        dc = YFixed;
    }

    RubberRect* rub = new RubberRect(nil, nil, l, b, r, t);
    return new DragManip(
	v, rub, rel, tool, DragConstraint(dc | Gravity), r, t
    );
}
