InsertAfter (Iterator i, GraphicView* v) {
    Elem(i)->Prepend(new UList(v));
    ++_count;
}
