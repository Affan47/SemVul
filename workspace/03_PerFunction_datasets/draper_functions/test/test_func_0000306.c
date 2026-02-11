test26_0 (bstring b0, int pos, int len, const_bstring b1, unsigned char fill, char * res) {
    bstring b2;
    int rv, ret = 0;

    if (b0 != NULL && b0->data != NULL && b0->slen >= 0 &&
            b1 != NULL && b1->data != NULL && b1->slen >= 0) {
        b2 = bstrcpy (b0);
        bwriteprotect (*b2);

        debug (".\tbreplace (%s, ", dumpBstring (b2));

        rv = breplace (b2, pos, len, b1, fill);
        ret += (rv == 0);
        if (!biseq (b0, b2)) ret++;

        debug ("%d, %d, %s, %02X) = %s", pos, len, dumpBstring (b1), fill, dumpBstring (b2));

        bwriteallow (*b2);

        debug (".\tbreplace (%s, ", dumpBstring (b2));

        rv = breplace (b2, pos, len, b1, fill);
        if (b1) {
            ret += (pos < 0) && (b2->slen != b0->slen);
            ret += ((rv == 0) != (pos >= 0 && pos <= b2->slen));
        }

        ret += (res == NULL) || ((int) strlen (res) > b2->slen)
            || (0 != memcmp (b2->data, res, b2->slen));
        ret += b2->data[b2->slen] != '\0';

        debug ("%d, %d, %s, %02X) = %s", pos, len, dumpBstring (b1), fill, dumpBstring (b2));

        bdestroy (b2);
    } else {
        ret += (BSTR_ERR != (rv = breplace (b0, pos, len, b1, fill)));
        debug (".\tbreplace (%s, %d, %d, %s, %02X) = %d", dumpBstring (b0), pos, len, dumpBstring (b1), fill, rv);
    }

    if (ret) {
        debug ("\t\tfailure(%d) = %d (res = %p", __LINE__, ret, res);
        if (res) debug (" = \"%s\"", res);
        debug (")");
    }
    return ret;
}
