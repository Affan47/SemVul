_PyExc_Fini(void)
{
    Py_CLEAR(PyExc_RecursionErrorInst);
    free_preallocated_memerrors();
    Py_CLEAR(errnomap);
}
