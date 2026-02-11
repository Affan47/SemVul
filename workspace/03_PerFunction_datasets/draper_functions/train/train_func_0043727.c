test46_1 (bstring b, const char * fmt, const_bstring r, ...) {
    int ret;

    debug (".\tbvformata (&, %s, \"%s\", ...) -> ", dumpBstring (b), fmt);
    bvformata (ret, b, fmt, r);
    debug ("%d, %s (%s)", ret, dumpBstring (b), dumpBstring (r));
    if (ret < 0) return (NULL != r);
    ret += 1 != biseq (r, b);
    if (0 != ret) debug ("\t->failed");
    return ret;
}
