CreateGraphicCompManip (
    Viewer* v, Event& e, Transformer* rel, Tool* tool
) {
    v->Constrain(e.x, e.y);
    Rubberband* rub = new RubberRect(nil, nil, e.x, e.y, e.x, e.y);
    return new DragManip(v, rub, rel, tool, DragConstraint(XYEqual | Gravity));
}
