auparse_callback(auparse_state_t *au, auparse_cb_event_t cb_event_type, void *user_data)
{
    CallbackData *cb = (CallbackData *)user_data;
    PyObject *arglist;
    PyObject *result;

    arglist = Py_BuildValue("OiO", cb->py_AuParser, cb_event_type, cb->user_data);
    result = PyEval_CallObject(cb->func, arglist);
    Py_DECREF(arglist);
    Py_XDECREF(result);
}
