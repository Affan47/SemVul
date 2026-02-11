_PyCode_CheckLineNumber(PyCodeObject* co, int lasti, PyAddrPair *bounds)
{
    Py_ssize_t size;
    int addr, line;
    unsigned char* p;

    p = (unsigned char*)PyBytes_AS_STRING(co->co_lnotab);
    size = PyBytes_GET_SIZE(co->co_lnotab) / 2;

    addr = 0;
    line = co->co_firstlineno;
    assert(line > 0);


    bounds->ap_lower = 0;
    while (size > 0) {
        if (addr + *p > lasti)
            break;
        addr += *p++;
        if (*p)
            bounds->ap_lower = addr;
        line += *p++;
        --size;
    }

    if (size > 0) {
        while (--size >= 0) {
            addr += *p++;
            if (*p++)
                break;
        }
        bounds->ap_upper = addr;
    }
    else {
        bounds->ap_upper = INT_MAX;
    }

    return line;
}
