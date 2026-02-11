is_same_dt_info(Module_table *mpt,
                Dt_info *src,
                Dt_info *dst)
{
    if (src->kind != dst->kind
        || src->src_sem->entry != dst->src_sem->entry
        || src->localize_mt != dst->localize_mt
        || !check_same_array_du_table(mpt,
                                      src->src_sem,
                                      dst->src_sem))
        return FALSE;
    return TRUE;
}
