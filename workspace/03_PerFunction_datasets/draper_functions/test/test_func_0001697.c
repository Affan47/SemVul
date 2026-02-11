dblayer_bt_compare(DB *db, const DBT *dbt1, const DBT *dbt2)
{
    struct berval bv1, bv2;
    value_compare_fn_type syntax_cmp_fn = (value_compare_fn_type)db->app_private;

    if ((dbt1->data && (dbt1->size>1) && (*((char*)dbt1->data) == EQ_PREFIX)) &&
        (dbt2->data && (dbt2->size>1) && (*((char*)dbt2->data) == EQ_PREFIX))) {
        bv1.bv_val = (char *)dbt1->data+1;
        bv1.bv_len = (ber_len_t)dbt1->size-1;

        bv2.bv_val = (char *)dbt2->data+1;
        bv2.bv_len = (ber_len_t)dbt2->size-1;

        return syntax_cmp_fn(&bv1, &bv2);
    }


    bv1.bv_val = (char *)dbt1->data;
    bv1.bv_len = (ber_len_t)dbt1->size;

    bv2.bv_val = (char *)dbt2->data;
    bv2.bv_len = (ber_len_t)dbt2->size;

    return slapi_berval_cmp(&bv1, &bv2);
}
