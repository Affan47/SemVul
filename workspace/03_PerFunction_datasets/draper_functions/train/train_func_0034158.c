test21_1 (bstring b, const_bstring sc, int ns) {
    struct bstrList * l;
    int ret = 0;

    debug (".\tbsplitstr (%s, %s) = ", dumpBstring (b), dumpBstring (sc));

    if (b != NULL && b->data != NULL && b->slen >= 0) {
        bstring c;

        debug ("{");

        l = bsplitstr (b, sc);

        if (l) {
            int i;
            for (i=0; i < l->qty; i++) {
                if (i != 0) debug (", ");
                debug ("%s", dumpBstring (l->entry[i]));
            }
            debug (":<%d>", l->qty);
            if (ns != l->qty) ret++;
        } else {
            debug ("NULL");
            ret ++;
        }

        debug ("}");

        c = bjoin (l, sc);
        ret += !biseq (c, b);
        bdestroy (c);
        ret += 0 != bstrListDestroy (l);
    } else {
        l = bsplitstr (b, sc);
        ret += (l != NULL);
        debug ("%p", (void *) l);
    }

    if (ret) {
        debug ("\t\tfailure(%d) ns = %d", __LINE__, ns);
    }

    return ret;
}
