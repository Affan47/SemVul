posix_tmpfile(PyObject *self, PyObject *noargs)
{
    FILE *fp;

    if (PyErr_WarnPy3k("tmpfile has been removed in 3.x; "
                       "use the tempfile module", 1) < 0)
        return NULL;

    fp = tmpfile();
    if (fp == NULL)
        return posix_error();
    return PyFile_FromFile(fp, "<tmpfile>", "w+b", fclose);
}
