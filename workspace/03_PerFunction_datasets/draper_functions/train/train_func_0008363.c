test40_0 (bstring b0, const_bstring b1, int left, int len, const char * res) {
    bstring b2;
    int rv, ret = 0;

    if (b0 != NULL && b0->data != NULL && b0->slen >= 0 &&
            b1 != NULL && b1->data != NULL && b1->slen >= 0) {
        b2 = bstrcpy (b0);
        bwriteprotect (*b2);

        debug (".\tbassignmidstr (%s, ", dumpBstring (b2));

        rv = bassignmidstr (b2, b1, left, len);
        ret += (rv == 0);
        if (!biseq (b0, b2)) ret++;

        debug ("%s, %d, %d) = %s", dumpBstring (b1), left, len, dumpBstring (b2));

        bwriteallow (*b2);

        debug (".\tbassignmidstr (%s, ", dumpBstring (b2));

        rv = bassignmidstr (b2, b1, left, len);

        debug ("%s, %d, %d) = %s", dumpBstring (b1), left, len, dumpBstring (b2));

        if (b1) ret += (b2->slen > len) | (b2->slen < 0);
        ret += ((0 != rv) && (b1 != NULL)) || ((0 == rv) && (b1 == NULL));
        ret += (res == NULL) || ((int) strlen (res) != b2->slen)
            || (0 != memcmp (b2->data, res, b2->slen));
        ret += b2->data[b2->slen] != '\0';
        bdestroy (b2);
    } else {
        ret += (BSTR_ERR != (rv = bassignmidstr (b0, b1, left, len)));
        debug (".\tbassignmidstr (%s, %s, %d, %d) = %d", dumpBstring (b0), dumpBstring (b1), left, len, rv);
    }

    if (ret) {
        debug ("\t\tfailure(%d) = %d (res = %p", __LINE__, ret, res);
        if (res) debug (" = \"%s\"", res);
        debug (")");
    }
    return ret;
}
