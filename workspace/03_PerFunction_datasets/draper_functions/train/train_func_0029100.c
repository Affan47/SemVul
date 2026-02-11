visit_obj_cb(hid_t UNUSED group_id, const char *name, const H5O_info_t *oinfo,
    void *_op_data)
{
    ovisit_ud_t *op_data = (ovisit_ud_t *)_op_data;


    if(HDstrcmp(op_data->info[op_data->idx].path, name)) return(H5_ITER_ERROR);
    if(op_data->info[op_data->idx].type != oinfo->type) return(H5_ITER_ERROR);


    op_data->idx++;

    return(H5_ITER_CONT);
}
