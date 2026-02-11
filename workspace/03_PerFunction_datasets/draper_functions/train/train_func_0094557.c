Copy () {
    Arrowhead* head = Head() ? (Arrowhead*) _head->Copy() : nil;
    Arrowhead* tail = Tail() ? (Arrowhead*) _tail->Copy() : nil;
    Coord* x, *y;
    const Coord* cx, * cy;
    int count = GetOriginal(cx, cy);
    x = (Coord*)cx; y = (Coord*)cy;

    return new ArrowOpenBSpline(x, y, count, head, tail, _arrow_scale, this);
}
