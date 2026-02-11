discard_for_fix_slot_no_dlg(Block *discard, Stasche_lm_dt *sld)
{
    List *li;
    List ***dbs = sld->discard_block_slot;
    int pgno;

    if (!flg_lad_multi_module_div || !cmp_fix_slot_no_dlg
        || discard->tlg_tag == -1
        || dbs[discard->tlg_tag][discard->loop_order] == NULL) {
        return ;
    }
    pgno = sld->taskexepro[discard->no];
    for (li = dbs[discard->tlg_tag][discard->loop_order];
         li != NULL;
         li = li->next) {
        Discard_slot_info *dsi = li->data;

        discard_slot_by_no_and_kind(discard->module, discard,
                                    pgno, sld, dsi->no,
                                    dsi->class, FALSE);
    }
}
