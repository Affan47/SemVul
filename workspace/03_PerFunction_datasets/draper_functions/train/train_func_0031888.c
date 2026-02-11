apply_termcap_settings(Console_IO_t * const mfp)
{
    const char *term_name;
    char    term_buff[2048];
    char   *tp;
    char    tc[10];
    int     val;


    if ((term_name = getenv("TERM")) == NULL) {


        return;


    }
    if (tgetent(term_buff, term_name) != 1) {


        return;


    }

    val = tgetnum("co");
    if (val >= 40 && val <= 512)
        mfp->disp_width = val;
    val = tgetnum("li");
    if (val >= 16 && val <= 256)
        mfp->disp_height = val;

    *(tp = tc) = '\0';
    tp = tgetstr("up", &tp);
    if (tp != NULL)
        strcpy(mfp->str_up, tp);

    *(tp = tc) = '\0';
    tp = tgetstr("ce", &tp);
    if (tp != NULL)
        strcpy(mfp->str_clreoln, tp);

    *(tp = tc) = '\0';
    tp = tgetstr("md", &tp);
    if (tp != NULL)
        strcpy(mfp->str_emph, tp);

    *(tp = tc) = '\0';
    tp = tgetstr("me", &tp);
    if (tp != NULL)
        strcpy(mfp->str_norm, tp);
}
