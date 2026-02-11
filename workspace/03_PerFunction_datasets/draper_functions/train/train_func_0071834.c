calc_plps_mt_start_time(int target_proc,
                        int target_mt,
                        double mt_start,
                        DtScheInfo *dt_sche,
                        Transfer_model *model)
{
    List *dtp_list;
    Module_table *mpt;
    double tmp;
    static DtScheInfo *dtmp;
    extern Boolean init_global_dt_flg;

    if (init_global_dt_flg) {
        dtmp = alloc_dt_sche_info();
        init_array_pred_succ(dt_sche);
        dtmp->array_pred = dt_sche->array_pred;
        init_global_dt_flg = FALSE;
    } else {
        dt_sche->array_pred = dtmp->array_pred;
    }
    mpt = dt_sche->block[1]->module;
    dtp_list = get_mt_dtp_list(target_proc, target_mt, dt_sche);
    if (dtp_list == NULL)
        return mt_start;
    dtp_list = add_sorted_dtp_list(NULL, dtp_list, mpt);
    tmp = calc_cmp_dtp_list(dtp_list, target_proc, target_mt, dt_sche, model);
    return mt_start < tmp ? tmp : mt_start;
}
