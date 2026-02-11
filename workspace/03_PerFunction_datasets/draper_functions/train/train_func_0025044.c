_wrap_GooCanvasItem__proxy_do_is_visible(GooCanvasItem *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;

    __py_state = pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }


    py_method = PyObject_GetAttrString(py_self, "do_is_visible");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }

    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;

    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);

    return retval;
}
