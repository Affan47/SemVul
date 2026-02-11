Iload (int argc, lvar_t *argv) {
    Psrc_t src;
    char *fn;
    FILE *fp;
    Tobj co;

    if ((fn = Tgetstring (argv[0].o))) {
        if (fn[0] == '-' && fn[1] == '\000')
            fp = stdin;
        else {
            fp = NULL;
            if ((fn = buildpath (fn, FALSE)))
                fp = fopen (fn, "r");
        }
        if (fp) {
            src.flag = FILESRC, src.s = NULL, src.fp = fp;
            src.tok = -1, src.lnum = 1;
            while ((co = Punit (&src)))
                Eoktorun = TRUE, Eunit (co);
            if (fp != stdin)
                fclose (fp);
        } else
            return L_FAILURE;
    }
    return L_SUCCESS;
}
