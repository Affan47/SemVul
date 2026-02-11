GFXsplinegon (int argc, lvar_t *argv) {
    Tobj po;
    Ggattr_t gattr;
    long i, pn;
    int wi;

    if (
        getint (argv[0].o, &wi) == -1 || !ISAWIDGET (wi) || !ISACANVAS2 (wi) ||
        getgattr ((argc == 4) ? argv[3].o : NULL, &gattr) == -1
    )
        return L_FAILURE;
    po = argv[2].o;
    if ((pn = Tgettablen (po)) > gpn) {
        gpp = Marraygrow (gpp, (long) pn * GPSIZE);
        gpn = pn;
    }
    for (i = 0; i < pn; i++)
        if (getxy (Tfindi (po, i), &gpp[i]) == -1)
            return L_FAILURE;
    Gsplinegon (wi, pn, gpp, &gattr);
    return L_SUCCESS;
}
