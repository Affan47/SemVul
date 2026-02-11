makeTitle(const char *fname) {
    const char *rslash = strrchr(fname, '/');
    if (rslash) rslash++;
    else        rslash = fname;

    char *name = strdup(rslash);
    char *rdot = strrchr(name, '.');

    PlotType pt  = PT_UNKNOWN;
    if (rdot) pt = string2PlotType(rdot+1);

    static char *title = 0;
    freeset(title, 0);

    if (pt == PT_UNKNOWN) {
        title = GBS_global_string_copy("%s (unknown type)", name);
    }
    else {
        rdot[0] = 0;
        title = GBS_global_string_copy("%s (%s)", name, plotTypeDescription[pt]);
    }

    free(name);

    return title;
}
