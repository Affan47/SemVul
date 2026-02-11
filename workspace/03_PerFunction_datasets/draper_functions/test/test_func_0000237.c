Prepend (AttributeValue* v) {
    _alist->Prepend(new AList(v));
    ++_count;
}
