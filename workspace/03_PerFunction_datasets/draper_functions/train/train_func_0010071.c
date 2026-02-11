cx_deque_remove(cx_deque *deque, cxcptr data)
{

    cx_deque_iterator first;


    cx_assert(deque != NULL);

    first = _cx_deque_begin(deque);

    while (first != _cx_deque_end(deque)) {

        if (_cx_deque_get(deque, first) == data) {
            _cx_deque_extract(deque, first);
        }
        else {
            first = _cx_deque_next(deque, first);
        }

    }

    return;

}
