test18_1_int (bstring b, int len, int res, int mlen, int __line__) {
    int ret = 0;
    int rv;
    int ol = 0;

    debug (".\tballocmin (%s, %d) = ", dumpBstring (b), len);
    if (b) ol = b->mlen;

    rv = ballocmin (b, len);
    debug ("[%d] %d", __LINE__, rv);

    if (b != NULL && b->data != NULL && b->mlen != mlen) {
        debug ("\t\t[%d] failure(%d) oldmlen = %d, newmlen = %d, mlen = %d len = %d", __line__, __LINE__, ol, b->mlen, mlen, b->slen);
        ret++;
    }

    if (rv != res) {
        debug ("\t\t[%d] failure(%d) res = %d", __line__, __LINE__, res);
        ret++;
    }

    return ret;
}
