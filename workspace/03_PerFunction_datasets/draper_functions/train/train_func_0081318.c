li_add_to_heap(li_object *obj) {
    int i;

    if (!_heap.objs) {
        _heap.cap = 1024;
        _heap.size = 0;
        _heap.objs = li_allocate(li_null, _heap.cap, sizeof(*_heap.objs));

        for (i = 0; i < HASHSIZE; i++)
            _syms[i] = li_null;
    } else if (_heap.size == _heap.cap) {
        _heap.cap *= 2;
        _heap.objs = li_allocate(_heap.objs, _heap.cap, sizeof(*_heap.objs));
    }
    _heap.objs[_heap.size++] = obj;
}
