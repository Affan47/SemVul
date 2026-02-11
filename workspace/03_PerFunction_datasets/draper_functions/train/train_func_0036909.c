nitro_BuildBuffer ( uint8* buf, uint32 len ) {
        PyObject* buf_obj = PyCObject_FromVoidPtr((void*)buf, NULL);
        PyObject* arg = Py_BuildValue ( "OI", buf_obj, len );
        PyObject* ret = PyObject_CallObject ( (PyObject*)&nitro_BufferType, arg );
        Py_DECREF(arg);
        Py_DECREF(buf_obj);
        return ret;
}
