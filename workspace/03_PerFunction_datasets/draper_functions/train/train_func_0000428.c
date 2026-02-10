get_dt_table(const int mtno,
             const dt_kind kind,
             const Array_def_use_table *src_du,
             const Array_def_use_table *dst_du,
             const int vpe_no)
{
    Dt_table *dt_head = NULL, *dpt = NULL;
    Array_region_list *src_reg, *dst_reg;
    int dim;

    if (src_du == NULL || dst_du == NULL) return NULL;

    dim = get_array_def_use_table_dim(src_du);
    for (src_reg = src_du->region_head, dst_reg = dst_du->region_head;
         src_reg != NULL && dst_reg != NULL;
         src_reg = src_reg->next, dst_reg = dst_reg->next) {
        if (dt_head == NULL) {
            dt_head = dpt = alloc_dt_table();
        } else {
            dpt->next = alloc_dt_table();
            dpt->next->prev = dpt;
            dpt = dpt->next;
        }
        dpt->mt_no = mtno;

        dpt->dt_info = alloc_dt_info();
        dpt->dt_info->kind = kind;

        dpt->dt_info->vpe_no = vpe_no;
        dpt->dt_info->src_data
            = array_reg_2_lio(src_reg, src_du->entry, dim);
        dpt->dt_info->dst_data
            = array_reg_2_lio(dst_reg, dst_du->entry, dim);

        dpt->dt_info->src_array_du = alloc_array_def_use_table();
        dpt->dt_info->src_array_du->entry = src_du->entry;
        dpt->dt_info->src_array_du->region_head
            = copy_array_region(src_reg);

        dpt->dt_info->dst_array_du = alloc_array_def_use_table();
        dpt->dt_info->dst_array_du->entry = dst_du->entry;
        dpt->dt_info->dst_array_du->region_head
            = copy_array_region(dst_reg);
    }
    if (dt_head == NULL) {
        dt_head = get_dt_table(mtno, kind, src_du->next, dst_du->next, vpe_no);
    } else {
        dpt->next = get_dt_table(mtno, kind, src_du->next,
                                 dst_du->next, vpe_no);
        if (dpt->next != NULL) {
            dpt->next->prev = dpt;
        }
    }
    return dt_head;
}
