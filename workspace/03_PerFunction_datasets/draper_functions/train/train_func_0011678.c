PyMySQLConnect(const char *dbfilename, const char *user, const char *password, const char *hostname)
{
    int iret;
    PyObject *ret;

    const char *host = hostname ? hostname : "";

    char *buf = g_strdup_printf("PyMySQLConnect(r'%s', '%s', '%s', '%s')", dbfilename, user, password, host);

    ret = PyRun_String(buf, Py_eval_input, pdict, pdict);
    g_free(buf);
    if (ret == NULL || !PyInt_Check(ret) || (iret = PyInt_AsLong(ret)) < 0) {
        PyErr_Print();
        return -1;
    } else if (iret == 0) {
        return 0;
    }
    return 1;
}
