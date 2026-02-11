ir_set_norm(IndexReader *ir, int doc_num, const char *field, uchar val)
{
    int field_num = fis_get_field_num(ir->fis, field);
    if (field_num >= 0) {
        ir_set_norm_i(ir, doc_num, field_num, val);
    }
}
