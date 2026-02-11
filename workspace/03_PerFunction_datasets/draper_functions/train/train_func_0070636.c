CreateManipulator (
    Viewer* v, Event& e, Transformer* rel, Tool* tool
) {
    Coord x0, y0, x1, y1;
    Rubberband* rub = nil;
    Manipulator* m = nil;

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        m = CreateLinkCompManip(v, e, rel, tool);

    } else if (tool->IsA(MOVE_TOOL)) {
        GetEndpoints(x0, y0, x1, y1);
	rub = new SlidingLine(nil, nil, x0, y0, x1, y1, e.x, e.y);
        m = new DragManip(v, rub, rel, tool, Gravity);

    } else if (tool->IsA(SCALE_TOOL)) {
        GetEndpoints(x0, y0, x1, y1);
        rub = new ScalingLine(nil, nil, x0, y0, x1, y1, (x0+x1)/2, (y0+y1)/2);
        m = new DragManip(v, rub, rel, tool, Gravity);

    } else if (tool->IsA(ROTATE_TOOL)) {
        GetEndpoints(x0, y0, x1, y1);
        rub = new RotatingLine(
            nil, nil, x0, y0, x1, y1, (x0+x1)/2, (y0+y1)/2, e.x, e.y
        );
        m = new DragManip(v, rub, rel, tool, Gravity);
    }
    return m;
}
