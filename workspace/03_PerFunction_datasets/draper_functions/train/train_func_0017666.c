_PyImport_Fini(void)
{
    Py_XDECREF(extensions);
    extensions = NULL;
    PyMem_DEL(_PyImport_Filetab);
    _PyImport_Filetab = NULL;
}
