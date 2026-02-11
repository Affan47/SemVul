GFXcreatebitmap (int argc, lvar_t *argv) {
    Tobj bo, so;
    Gsize_t s;
    long rtnm;
    int wi, bi;

    if (
        getint (argv[0].o, &wi) == -1 || !ISAWIDGET (wi) || !ISACANVAS2 (wi) ||
        getxy (argv[1].o, &s) == -1
    )
        return L_FAILURE;
    if ((bi = Gcreatebitmap (wi, s)) == -1)
        return L_FAILURE;
    Tinsi (rootbo, bi, (bo = Ttable (4)));
    rtno = Tinteger (bi);
    rtnm = Mpushmark (rtno);
    Tinss (bo, "canvas", Tinteger (bi));
    Tinss (bo, "size", (so = Ttable (2)));
    Tinss (so, "x", Tinteger ((long) Gbitmaps[bi].size.x));
    Tinss (so, "y", Tinteger ((long) Gbitmaps[bi].size.y));
    Mpopmark (rtnm);
    return L_SUCCESS;
}
