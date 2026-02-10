mar_parse_dqt (PJDEC_INST g)
{
    int   len, i;
    BYTE  pt;
    long *tbl_p;

    len = read_uint(g) - 2;

    while (len >= 65) {
        len -= 65;
        pt = read_byte (g);
        if ((pt & 0xfcu) != 0)
            longjmp (g->syntax_error, NOT_IMPLEMENTED);
        tbl_p = g->quant_tbls[pt & 3];
        DUMP (_T("\nDQT marker:  table=%d"), pt & 3, 0, 0);
        for (i=0; i<64; i++) {
            if ((i & 15) == 0) DUMP(_T("\n    "), 0,0,0);
            tbl_p[i] = read_byte (g);
            DUMP (_T("%2d "), tbl_p[i], 0, 0);
        }
        DUMP (_T("\n"), 0,0,0);
        wino_scale_table (tbl_p);
    }

    if (len != 0)
        longjmp (g->syntax_error, BAD_MARKER_DATA);
}
