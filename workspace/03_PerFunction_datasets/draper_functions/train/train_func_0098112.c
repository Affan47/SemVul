treebuilder_handle_namespace(TreeBuilderObject* self, int start,
                             PyObject *prefix, PyObject *uri)
{
    PyObject* res;
    PyObject* action;
    PyObject* parcel;

    if (!self->events)
        return;

    if (start) {
        if (!self->start_ns_event_obj)
            return;
        action = self->start_ns_event_obj;
        parcel = Py_BuildValue("OO", prefix, uri);
        if (!parcel)
            return;
        Py_INCREF(action);
    } else {
        if (!self->end_ns_event_obj)
            return;
        action = self->end_ns_event_obj;
        Py_INCREF(action);
        parcel = Py_None;
        Py_INCREF(parcel);
    }

    res = PyTuple_New(2);

    if (res) {
        PyTuple_SET_ITEM(res, 0, action);
        PyTuple_SET_ITEM(res, 1, parcel);
        PyList_Append(self->events, res);
        Py_DECREF(res);
    } else
        PyErr_Clear();
}
