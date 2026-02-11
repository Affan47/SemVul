_find_btl_id(mca_bml_base_btl_t *bml_btl)
{
    int i;

    for (i = 0; i < mca_spml_yoda.n_btls; i++) {
        if (mca_spml_yoda.btl_type_map[i].btl == bml_btl->btl)
            return i;
    }
    return -1;
}
