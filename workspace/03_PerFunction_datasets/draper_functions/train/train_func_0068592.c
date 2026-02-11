deque_del_item(dequeobject *deque, Py_ssize_t i)
{
    PyObject *item;

    assert (i >= 0 && i < Py_SIZE(deque));
    if (_deque_rotate(deque, -i) == -1)
        return -1;

    item = deque_popleft(deque, NULL);
    assert (item != NULL);
    Py_DECREF(item);

    return _deque_rotate(deque, i);
}
