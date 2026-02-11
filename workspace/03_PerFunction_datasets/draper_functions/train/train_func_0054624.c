mbuf_copy_format(_PyManagedBufferObject *mbuf, const char *fmt)
{
    if (fmt != NULL) {
        char *cp = PyMem_Malloc(strlen(fmt)+1);
        if (cp == NULL) {
            PyErr_NoMemory();
            return -1;
        }
        mbuf->master.format = strcpy(cp, fmt);
        mbuf->flags |= _Py_MANAGED_BUFFER_FREE_FORMAT;
    }

    return 0;
}
