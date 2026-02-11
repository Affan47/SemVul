load_next(PyObject *mod, PyObject *altmod, char **p_name, char *buf,
          Py_ssize_t *p_buflen)
{
    char *name = *p_name;
    char *dot = strchr(name, '.');
    size_t len;
    char *p;
    PyObject *result;

    if (strlen(name) == 0) {


        Py_INCREF(mod);
        *p_name = NULL;
        return mod;
    }

    if (dot == NULL) {
        *p_name = NULL;
        len = strlen(name);
    }
    else {
        *p_name = dot+1;
        len = dot-name;
    }
    if (len == 0) {
        PyErr_SetString(PyExc_ValueError,
                        "Empty module name");
        return NULL;
    }

    p = buf + *p_buflen;
    if (p != buf)
        *p++ = '.';
    if (p+len-buf >= MAXPATHLEN) {
        PyErr_SetString(PyExc_ValueError,
                        "Module name too long");
        return NULL;
    }
    strncpy(p, name, len);
    p[len] = '\0';
    *p_buflen = p+len-buf;

    result = import_submodule(mod, p, buf);
    if (result == Py_None && altmod != mod) {
        Py_DECREF(result);

        result = import_submodule(altmod, p, p);
        if (result != NULL && result != Py_None) {
            if (mark_miss(buf) != 0) {
                Py_DECREF(result);
                return NULL;
            }
            strncpy(buf, name, len);
            buf[len] = '\0';
            *p_buflen = len;
        }
    }
    if (result == NULL)
        return NULL;

    if (result == Py_None) {
        Py_DECREF(result);
        PyErr_Format(PyExc_ImportError,
                     "No module named %.200s", name);
        return NULL;
    }

    return result;
}
