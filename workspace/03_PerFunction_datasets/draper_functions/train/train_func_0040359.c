_wrap_GooCanvasItemModel__proxy_do_get_child(GooCanvasItemModel *self, gint child_num)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_child_num;
    GooCanvasItemModel* retval;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;

    __py_state = pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    py_child_num = PyInt_FromLong(child_num);

    py_args = PyTuple_New(1);
    PyTuple_SET_ITEM(py_args, 0, py_child_num);

    py_method = PyObject_GetAttrString(py_self, "do_get_child");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    if (py_retval == Py_None) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    if (!PyObject_TypeCheck(py_retval, &PyGObject_Type)) {
        PyErr_SetString(PyExc_TypeError, "retval should be a GObject");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    retval = (GooCanvasItemModel*) pygobject_get(py_retval);
    g_object_ref((GObject *) retval);


    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);

    return retval;
}
