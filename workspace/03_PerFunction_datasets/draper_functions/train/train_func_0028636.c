converttuple(PyObject *arg, const char **p_format, va_list *p_va, int flags,
             int *levels, char *msgbuf, size_t bufsize, int toplevel,
             freelist_t *freelist)
{
    int level = 0;
    int n = 0;
    const char *format = *p_format;
    int i;

    for (;;) {
        int c = *format++;
        if (c == '(') {
            if (level == 0)
                n++;
            level++;
        }
        else if (c == ')') {
            if (level == 0)
                break;
            level--;
        }
        else if (c == ':' || c == ';' || c == '\0')
            break;
        else if (level == 0 && isalpha(Py_CHARMASK(c)))
            n++;
    }

    if (!PySequence_Check(arg) || PyBytes_Check(arg)) {
        levels[0] = 0;
        PyOS_snprintf(msgbuf, bufsize,
                      toplevel ? "expected %d arguments, not %.50s" :
                      "must be %d-item sequence, not %.50s",
                  n,
                  arg == Py_None ? "None" : arg->ob_type->tp_name);
        return msgbuf;
    }

    if ((i = PySequence_Size(arg)) != n) {
        levels[0] = 0;
        PyOS_snprintf(msgbuf, bufsize,
                      toplevel ? "expected %d arguments, not %d" :
                     "must be sequence of length %d, not %d",
                  n, i);
        return msgbuf;
    }

    format = *p_format;
    for (i = 0; i < n; i++) {
        char *msg;
        PyObject *item;
        item = PySequence_GetItem(arg, i);
        if (item == NULL) {
            PyErr_Clear();
            levels[0] = i+1;
            levels[1] = 0;
            strncpy(msgbuf, "is not retrievable", bufsize);
            return msgbuf;
        }
        msg = convertitem(item, &format, p_va, flags, levels+1,
                          msgbuf, bufsize, freelist);

        Py_XDECREF(item);
        if (msg != NULL) {
            levels[0] = i+1;
            return msg;
        }
    }

    *p_format = format;
    return NULL;
}
