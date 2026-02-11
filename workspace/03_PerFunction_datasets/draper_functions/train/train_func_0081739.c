python_cleanup(void *data)
{
    interpreterdata *idata;

    cleanup_info *ci = (cleanup_info *)data;


    idata = get_interpreter(ci->interpreter);

    if (!idata) {
        Py_DECREF(ci->handler);
        Py_XDECREF(ci->data);
        free((void *)ci->interpreter);
        free(ci);
        return APR_SUCCESS;
    }


    if (! PyObject_CallFunction(ci->handler, "O", ci->data)) {
        PyObject *ptype;
        PyObject *pvalue;
        PyObject *ptb;
        PyObject *handler;
        PyObject *stype;
        PyObject *svalue;

        PyErr_Fetch(&ptype, &pvalue, &ptb);
        handler = PyObject_Str(ci->handler);
        stype = PyObject_Str(ptype);
        svalue = PyObject_Str(pvalue);

        Py_XDECREF(ptype);
        Py_XDECREF(pvalue);
        Py_XDECREF(ptb);

        if (ci->request_rec) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0,
                          ci->request_rec,
                          "python_cleanup: Error calling cleanup object %s",
                          PyString_AsString(handler));
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0,
                          ci->request_rec,
                          "    %s: %s", PyString_AsString(stype),
                          PyString_AsString(svalue));
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0,
                         ci->server_rec,
                         "python_cleanup: Error calling cleanup object %s",
                         PyString_AsString(handler));
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0,
                         ci->server_rec,
                         "    %s: %s", PyString_AsString(stype),
                         PyString_AsString(svalue));
        }

        Py_DECREF(handler);
        Py_DECREF(stype);
        Py_DECREF(svalue);
    }

    Py_DECREF(ci->handler);
    Py_DECREF(ci->data);
    free((void *)ci->interpreter);
    free(ci);

    release_interpreter();

    return APR_SUCCESS;
}
