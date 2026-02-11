extlg_includes_tlg(Expand_tlg *extlg0, Tlg *tlg1)
{
    LoopDat *lpdat1;

    for (lpdat1 = tlg1->lpdat_head; lpdat1 != NULL; lpdat1 = lpdat1->next) {
        if (!extlg_includes_block(extlg0, lpdat1->bpt)) {
            return FALSE;
        }
    }

    return TRUE;
}
