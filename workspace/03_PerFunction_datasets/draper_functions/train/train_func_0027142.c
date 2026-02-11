test42_0 (const_bstring bi, int len, const char * res) {
    bstring b;
    int rv, ret = 0;

    rv = btrunc (b = bstrcpy (bi), len);
    ret += (len >= 0) ? (rv < 0) : (rv >= 0);
    if (res) ret += (0 == biseqcstr (b, res));
    debug (".\tbtrunc (%s, %d) = %s", dumpBstring (bi), len, dumpBstring (b));
    bdestroy (b);
    return ret;
}
