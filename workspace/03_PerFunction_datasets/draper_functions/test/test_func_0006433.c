ir_terms_from(IndexReader *ir, const char *field,
                           const char *term)
{
    TermEnum *te = NULL;
    int field_num = fis_get_field_num(ir->fis, field);
    if (field_num >= 0) {
        te = ir->terms_from(ir, field_num, term);
    }
    return te;
}
