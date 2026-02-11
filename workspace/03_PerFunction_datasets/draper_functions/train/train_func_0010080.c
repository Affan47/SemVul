trval2(fp, enc, len, lev, rlen)
    FILE *fp;
    unsigned char *enc;
    int len;
    int lev;
    int *rlen;
{
    int l, eid, elen, xlen, r, rlen2 = 0;
    int rlen_ext = 0;

    r = OK;

    if (len < 2) {
        fprintf(fp, "missing id and length octets (%d)\n", len);
        return(NOTOK);
    }

    fprintf(fp, "\n");
    for (l=0; l<lev; l++) fprintf(fp, ".  ");

context_restart:
    eid = enc[0];
    elen = enc[1];

    if (print_id_and_len) {
        fprintf(fp, "%02x ", eid);
        fprintf(fp, "%02x ", elen);
    }

    if (elen == LEN_XTND) {
        fprintf(fp,
                "indefinite length encoding not implemented (0x%02x)\n", elen);
        return(NOTOK);
    }

    xlen = 0;
    if (elen & LEN_XTND) {
        xlen = elen & LEN_MASK;
        if (xlen > len - 2) {
            fprintf(fp, "extended length too long (%d > %d - 2)\n", xlen, len);
            return(NOTOK);
        }
        elen = decode_len(fp, enc+2, xlen);
    }

    if (elen > len - 2 - xlen) {
        fprintf(fp, "length too long (%d > %d - 2 - %d)\n", elen, len, xlen);
        return(NOTOK);
    }

    print_tag_type(fp, eid, lev);

    if (print_context_shortcut && (eid & ID_CLASS) == CLASS_CONT &&
        (eid & ID_FORM) == FORM_CONS && lev > 0) {
        rlen_ext += 2 + xlen;
        enc += 2 + xlen;
        fprintf(fp, " ");
        goto context_restart;
    }

    switch(eid & ID_FORM) {
    case FORM_PRIM:
        r = do_prim(fp, eid & ID_TAG, enc+2+xlen, elen, lev+1);
        *rlen = 2 + xlen + elen + rlen_ext;
        break;
    case FORM_CONS:
        if (print_constructed_length) {
            fprintf(fp, " constr");
            fprintf(fp, " <%d>", elen);
        }
        r = do_cons(fp, enc+2+xlen, elen, lev+1, &rlen2);
        *rlen = 2 + xlen + rlen2 + rlen_ext;
        break;
    }

    return(r);
}
