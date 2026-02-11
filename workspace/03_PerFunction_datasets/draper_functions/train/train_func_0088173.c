buffer_concat(PyBufferObject *self, PyObject *other)
{
    PyBufferProcs *pb = other->ob_type->tp_as_buffer;
    void *ptr1, *ptr2;
    char *p;
    PyObject *ob;
    Py_ssize_t size, count;

    if ( pb == NULL ||
         pb->bf_getreadbuffer == NULL ||
         pb->bf_getsegcount == NULL )
    {
        PyErr_BadArgument();
        return NULL;
    }
    if ( (*pb->bf_getsegcount)(other, NULL) != 1 )
    {

        PyErr_SetString(PyExc_TypeError,
                        "single-segment buffer object expected");
        return NULL;
    }

    if (!get_buf(self, &ptr1, &size, ANY_BUFFER))
        return NULL;


    if ( size == 0 )
    {
        Py_INCREF(other);
        return other;
    }

    if ( (count = (*pb->bf_getreadbuffer)(other, 0, &ptr2)) < 0 )
        return NULL;

    assert(count <= PY_SIZE_MAX - size);

    ob = PyString_FromStringAndSize(NULL, size + count);
    if ( ob == NULL )
        return NULL;
    p = PyString_AS_STRING(ob);
    memcpy(p, ptr1, size);
    memcpy(p + size, ptr2, count);


    p[size + count] = '\0';

    return ob;
}
