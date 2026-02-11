nitro_Buffer_SetItem(PyObject *o, Py_ssize_t i, PyObject *v) {

    nitro_BufferObject* self = (nitro_BufferObject*)o;

    if ( i > self->m_len-1 ) {
        PyErr_SetString(PyExc_Exception,"Out of bounds." );
        return -1;
    }

    long l = PyInt_AsLong(v);
    if (PyErr_Occurred()) { return -1; }
    self->m_buf[i] = (uint8) l;

    return 0;
}
