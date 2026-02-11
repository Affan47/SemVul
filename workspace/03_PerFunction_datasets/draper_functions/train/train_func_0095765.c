get_zc_ip_address(PyObject *self, PyObject *args)
{
    char *hn;
    char ip[HPMUD_BUFFER_SIZE];
    enum HPMUD_RESULT result = HPMUD_R_OK;

    if (!PyArg_ParseTuple(args, "s", &hn))
            return NULL;

    Py_BEGIN_ALLOW_THREADS
    result = hpmud_mdns_lookup(hn, HPMUD_MDNS_TIMEOUT, ip);
    Py_END_ALLOW_THREADS

    return Py_BuildValue("(is)", result, ip);
}
