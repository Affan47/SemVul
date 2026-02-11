dumpBstring (const struct tagbstring * b) {
    rot = (rot + 1) % (unsigned)16;
    if (dumpOut[rot] == NULL) {
        dumpOut[rot] = bfromcstr ("");
        if (dumpOut[rot] == NULL) return "FATAL INTERNAL ERROR";
    }
    dumpOut[rot]->slen = 0;
    if (b == NULL) {
        bcatcstr (dumpOut[rot], "NULL");
    } else {
        static char msg[256];
        sprintf(msg, "%p", (void *)b);
        bcatcstr (dumpOut[rot], msg);

        if (b->slen < 0) {
            sprintf (msg, ":[err:slen=%d<0]", b->slen);
            bcatcstr (dumpOut[rot], msg);
        } else {
            if (b->mlen > 0 && b->mlen < b->slen) {
                sprintf (msg, ":[err:mlen=%d<slen=%d]", b->mlen, b->slen);
                bcatcstr (dumpOut[rot], msg);
            } else {
                if (b->mlen == -1) {
                    bcatcstr (dumpOut[rot], "[p]");
                } else if (b->mlen < 0) {
                    bcatcstr (dumpOut[rot], "[c]");
                }
                bcatcstr (dumpOut[rot], ":");
                if (b->data == NULL) {
                    bcatcstr (dumpOut[rot], "[err:data=NULL]");
                } else {
                    bcatcstr (dumpOut[rot], "\"");
                    bcatcstr (dumpOut[rot], (const char *) b->data);
                    bcatcstr (dumpOut[rot], "\"");
                }
            }
        }
    }
    return (char *) dumpOut[rot]->data;
}
