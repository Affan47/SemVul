func_init(void)
{
    extern int    vtrow;
    extern int    vtcol;
    extern int    lbound;


    fillcol = (term.t_ncol > 80) ? 77 : term.t_ncol - 6;
    sgarbf = TRUE;
    mpresf = FALSE;
    mline_open = FALSE;
    ComposerEditing = FALSE;


    vtrow = vtcol = lbound = 0;
    clearcursor();

    pat[0] = rpat[0] = '\0';
    browse_dir[0] = '\0';
}
