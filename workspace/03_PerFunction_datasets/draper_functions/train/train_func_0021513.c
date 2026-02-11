Punit (Psrc_t *sp) {
    int ui, ei;

    Lsetsrc (sp->flag, sp->s, sp->fp, sp->tok, sp->lnum);
    Creset ();
    flvi = llvi = 0;

    if (setjmp (eljbuf) != 0)
        return NULL;

    while (Ltok == L_SEMI)
        Lgtok ();
    if (Ltok == L_EOF)
        return NULL;

    ui = Cnew (C_CODE);
    ei = pexpr ();
    Csetfp (ui, ei);
    Lgetsrc (&sp->flag, &sp->s, &sp->fp, &sp->tok, &sp->lnum);
    return Tcode (cbufp, 0, cbufi);
}
