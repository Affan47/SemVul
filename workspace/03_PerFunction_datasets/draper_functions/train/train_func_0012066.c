is_strip_mining_tlg_assigned(const Tlg *tlg, int iter)
{
    LoopDat *lpdat;
    Boolean ret = TRUE;

    for (lpdat = tlg->lpdat_head; lpdat != NULL; lpdat = lpdat->next) {
        ret &= is_strip_mining_block_assigned(lpdat->bpt, iter);
    }
    return ret;
}
