Irun (int argc, lvar_t *argv) {
    Psrc_t src;
    char *s;
    Tobj co;

    if ((s = Tgetstring (argv[0].o))) {
        src.flag = CHARSRC, src.s = s, src.fp = NULL;
        src.tok = -1, src.lnum = 1;
        while ((co = Punit (&src)))
            Eoktorun = TRUE, Eunit (co);
    }
    return L_SUCCESS;
}
