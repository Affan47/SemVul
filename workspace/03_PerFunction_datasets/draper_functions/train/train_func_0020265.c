PyMember_GetOne(const char *addr, PyMemberDef *l)
{
    PyObject *v;

    addr += l->offset;
    switch (l->type) {
    case T_BOOL:
        v = PyBool_FromLong(*(char*)addr);
        break;
    case T_BYTE:
        v = PyLong_FromLong(*(char*)addr);
        break;
    case T_UBYTE:
        v = PyLong_FromUnsignedLong(*(unsigned char*)addr);
        break;
    case T_SHORT:
        v = PyLong_FromLong(*(short*)addr);
        break;
    case T_USHORT:
        v = PyLong_FromUnsignedLong(*(unsigned short*)addr);
        break;
    case T_INT:
        v = PyLong_FromLong(*(int*)addr);
        break;
    case T_UINT:
        v = PyLong_FromUnsignedLong(*(unsigned int*)addr);
        break;
    case T_LONG:
        v = PyLong_FromLong(*(long*)addr);
        break;
    case T_ULONG:
        v = PyLong_FromUnsignedLong(*(unsigned long*)addr);
        break;
    case T_PYSSIZET:
        v = PyLong_FromSsize_t(*(Py_ssize_t*)addr);
        break;
    case T_FLOAT:
        v = PyFloat_FromDouble((double)*(float*)addr);
        break;
    case T_DOUBLE:
        v = PyFloat_FromDouble(*(double*)addr);
        break;
    case T_STRING:
        if (*(char**)addr == NULL) {
            Py_INCREF(Py_None);
            v = Py_None;
        }
        else
            v = PyUnicode_FromString(*(char**)addr);
        break;
    case T_STRING_INPLACE:
        v = PyUnicode_FromString((char*)addr);
        break;
    case T_CHAR:
        v = PyUnicode_FromStringAndSize((char*)addr, 1);
        break;
    case T_OBJECT:
        v = *(PyObject **)addr;
        if (v == NULL)
            v = Py_None;
        Py_INCREF(v);
        break;
    case T_OBJECT_EX:
        v = *(PyObject **)addr;
        if (v == NULL)
            PyErr_SetString(PyExc_AttributeError, l->name);
        Py_XINCREF(v);
        break;
#ifdef HAVE_LONG_LONG
    case T_LONGLONG:
        v = PyLong_FromLongLong(*(PY_LONG_LONG *)addr);
        break;
    case T_ULONGLONG:
        v = PyLong_FromUnsignedLongLong(*(unsigned PY_LONG_LONG *)addr);
        break;
#endif
    case T_NONE:
        v = Py_None;
        Py_INCREF(v);
        break;
    default:
        PyErr_SetString(PyExc_SystemError, "bad memberdescr type");
        v = NULL;
    }
    return v;
}
