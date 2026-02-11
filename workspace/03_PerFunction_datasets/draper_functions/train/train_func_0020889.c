update_lastcheck(Stasche_lm_dt *sld, Slot *slot, const int mtno, const Pp pp)
{
    int idx, lidx;

    if (cmp_ya_templ) {
        update_lastcheck_by_no(sld, slot->no, slot->kind, slot->templ_kind,
                               mtno, pp, slot->lm);
    } else {
        if (slot->last_checkmt == -1) {
            slot->last_checkmt = mtno;
            slot->last_checkpp = pp;
        } else {
            idx = get_timing_index(sld, mtno, pp);
            lidx = get_timing_index(sld, slot->last_checkmt, slot->last_checkpp);
            if (idx > lidx) {
                slot->last_checkmt = mtno;
                slot->last_checkpp = pp;
            }
        }
    }
}
