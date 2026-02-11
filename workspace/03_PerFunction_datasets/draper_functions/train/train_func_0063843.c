mr_close_ext_i(IndexReader *ir)
{
    int **field_num_map = MR(ir)->field_num_map;
    if (field_num_map) {
        int i;
        for (i = MR(ir)->r_cnt - 1; i >= 0; i--) {
            free(field_num_map[i]);
        }
        free(field_num_map);
    }
    fis_deref(ir->fis);
    mr_close_i(ir);
}
