Copy () {
    Arrowhead* head = Head() ? (Arrowhead*) _head->Copy() : nil;
    Arrowhead* tail = Tail() ? (Arrowhead*) _tail->Copy() : nil;

    return new ArrowMultiLine(x(), y(), count(), head, tail, _arrow_scale, this);
}
