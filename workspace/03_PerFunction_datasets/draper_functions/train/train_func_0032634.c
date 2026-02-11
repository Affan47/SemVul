mr_open(IndexReader **sub_readers, const int r_cnt)
{
    IndexReader *ir = mr_new(sub_readers, r_cnt);
    MultiReader *mr = MR(ir);

    FieldInfos *fis = fis_new(0, 0, 0);
    int i, j;
    bool need_field_map = false;


    for (i = 0; i < r_cnt; i++) {
        FieldInfos *sub_fis = sub_readers[i]->fis;
        const int sub_fis_size = sub_fis->size;
        for (j = 0; j < sub_fis_size; j++) {
            FieldInfo *fi = sub_fis->fields[j];
            FieldInfo *new_fi = fis_get_or_add_field(fis, fi->name);
            new_fi->bits |= fi->bits;
            if (fi->number != new_fi->number) {
                need_field_map = true;
            }
        }
    }


    if (need_field_map) {
        mr->field_num_map = ALLOC_N(int *, r_cnt);
        for (i = 0; i < r_cnt; i++) {
            FieldInfos *sub_fis = sub_readers[i]->fis;
            const int fis_size = fis->size;

            mr->field_num_map[i] = ALLOC_N(int, fis_size);
            for (j = 0; j < fis_size; j++) {
                FieldInfo *fi = fis->fields[j];
                FieldInfo *fi_sub = fis_get_field(sub_fis, fi->name);


                mr->field_num_map[i][j] = fi_sub ? fi_sub->number : -1;
            }
        }


    }
    else {
        mr->field_num_map = NULL;
    }


    ir->close_i = &mr_close_ext_i;

    return ir_setup(ir, NULL, NULL, fis, false);
}
