objToString(MprBuf *buf, MprObj *obj, int type, int pretty)
{
    MprKey  *kp;
    char    numbuf[32];
    int     i, len;

    if (type == MPR_JSON_ARRAY) {
        mprPutCharToBuf(buf, '[');
        if (pretty) mprPutCharToBuf(buf, '\n');
        len = mprGetHashLength(obj);
        for (i = 0; i < len; i++) {
            itosbuf(numbuf, sizeof(numbuf), i, 10);
            if (pretty) mprPutStringToBuf(buf, "    ");
            if ((kp = mprLookupKeyEntry(obj, numbuf)) == 0) {
                mprAssert(kp);
                continue;
            }
            if (kp->type == MPR_JSON_ARRAY || kp->type == MPR_JSON_OBJ) {
                objToString(buf, (MprObj*) kp->data, kp->type, pretty);
            } else {
                quoteValue(buf, kp->data);
            }
            mprPutCharToBuf(buf, ',');
            if (pretty) mprPutCharToBuf(buf, '\n');
        }
        mprPutCharToBuf(buf, ']');

    } else if (type == MPR_JSON_OBJ) {
        mprPutCharToBuf(buf, '{');
        if (pretty) mprPutCharToBuf(buf, '\n');
        for (ITERATE_KEYS(obj, kp)) {
            if (kp->key == 0 || kp->data == 0) continue;
            if (pretty) mprPutStringToBuf(buf, "    ");
            mprPutStringToBuf(buf, kp->key);
            mprPutStringToBuf(buf, ": ");
            if (kp->type == MPR_JSON_ARRAY || kp->type == MPR_JSON_OBJ) {
                objToString(buf, (MprObj*) kp->data, kp->type, pretty);
            } else {
                quoteValue(buf, kp->data);
            }
            mprPutCharToBuf(buf, ',');
            if (pretty) mprPutCharToBuf(buf, '\n');
        }
        mprPutCharToBuf(buf, '}');
    }
    if (pretty) mprPutCharToBuf(buf, '\n');
    return sclone(mprGetBufStart(buf));
}
