test36_0 (const_bstring b0, const_bstring b1, int n, int res) {
    int rv, ret = 0;

    ret += (res != (rv = bstrnicmp (b0, b1, n)));
    debug (".\tbstrnicmp (%s, %s, %d) = %d", dumpBstring (b0), dumpBstring (b1), n, rv);
    if (ret) {
        debug ("\t\tfailure(%d) = %d (res = %d)", __LINE__, ret, res);
    }
    return ret;
}
