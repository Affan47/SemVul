save_int(PicklerObject *self, long x)
{
    char pdata[32];
    Py_ssize_t len = 0;

    if (!self->bin
#if SIZEOF_LONG > 4
        || x > 0x7fffffffL || x < -0x80000000L
#endif
        ) {


        pdata[0] = LONG;
        PyOS_snprintf(pdata + 1, sizeof(pdata) - 1, "%ldL\n", x);
        if (_Pickler_Write(self, pdata, strlen(pdata)) < 0)
            return -1;
    }
    else {

        pdata[1] = (unsigned char)(x & 0xff);
        pdata[2] = (unsigned char)((x >> 8) & 0xff);
        pdata[3] = (unsigned char)((x >> 16) & 0xff);
        pdata[4] = (unsigned char)((x >> 24) & 0xff);

        if ((pdata[4] == 0) && (pdata[3] == 0)) {
            if (pdata[2] == 0) {
                pdata[0] = BININT1;
                len = 2;
            }
            else {
                pdata[0] = BININT2;
                len = 3;
            }
        }
        else {
            pdata[0] = BININT;
            len = 5;
        }

        if (_Pickler_Write(self, pdata, len) < 0)
            return -1;
    }

    return 0;
}
