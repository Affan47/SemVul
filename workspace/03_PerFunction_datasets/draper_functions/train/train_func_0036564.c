sp_desc_dump()
{
    SPFIELD *f;
    u_int i;

    for (f = spfields, i=0; i < sp_field_cnt; ++i, ++f){
        printf("field %s{\n", f->name);
        printf("\ttype: %s\n", f->type);
        printf("\tfunc: %s\n", f->func);
        printf("\textract_idx: %s\n", f->extract_idx);
        printf("}\n");
    }
    return 0;
}
