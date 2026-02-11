tlg_has_doacr(Tlg *tlg)
{
    LoopDat *p;

    for (p = tlg->lpdat_head; p != NULL; p = p->next) {
        if (p->bpt->kind == DOACR)
            return TRUE;
    }

    return FALSE;
}
