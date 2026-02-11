test44_0 (const char * str) {
    int ret = 0, v;
    bstring b = bfromcstr("");

    if (NULL == str) {
        ret += 0 <= bassigncstr (NULL, "test");
        debug (".\tbassigncstr (b = %s, NULL)", dumpBstring (b = bfromcstr ("")));
        ret += 0 <= (v = bassigncstr (b, NULL));
        debug (" = %d; b -> %s", v, dumpBstring (b));
        ret += 0 <= bassigncstr (&shortBstring, NULL);
        bdestroy (b);
        return ret;
    }

    ret += 0 <= bassigncstr (NULL, str);
    debug (".\tbassigncstr (b = %s, \"%s\")", dumpBstring (b = bfromcstr ("")), str);
    ret += 0 > (v = bassigncstr (b, str));
    debug (" = %d; b -> %s", v, dumpBstring (b));
    ret += 0 != strcmp (bdatae (b, ""), str);
    ret += ((size_t) b->slen) != strlen (str);
    ret += 0 > bassigncstr (b, "xxxxx");
    bwriteprotect(*b)
        log_info(".\tbassigncstr (b = %s, \"%s\")", dumpBstring (b), str);
    ret += 0 <= (v = bassigncstr (b, str));
    debug (" = %d; b -> %s", v, dumpBstring (b));
    ret += 0 != strcmp (bdatae (b, ""), "xxxxx");
    ret += ((size_t) b->slen) != strlen ("xxxxx");
    bwriteallow(*b)
        ret += 0 <= bassigncstr (&shortBstring, str);
    bdestroy (b);
    debug (".\tbassigncstr (a = %s, \"%s\")", dumpBstring (&shortBstring), str);
    ret += 0 <= (v = bassigncstr (&shortBstring, str));
    debug (" = %d; a -> %s", v, dumpBstring (&shortBstring));
    return ret;
}
