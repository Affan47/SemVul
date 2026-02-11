mca_spml_base_close(void)
{
    int i, j;


    OBJ_DESTRUCT(&mca_spml_base_put_requests);
    OBJ_DESTRUCT(&mca_spml_base_get_requests);


    j = opal_pointer_array_get_size(&mca_spml_base_spml);
    for (i = 0; i < j; i++) {
        char * tmp_val;
        tmp_val = (char *) opal_pointer_array_get_item(&mca_spml_base_spml, i);
        if (NULL == tmp_val) {
            continue;
        }
        free(tmp_val);
    }
    OBJ_DESTRUCT(&mca_spml_base_spml);


    return mca_base_framework_components_close(&oshmem_spml_base_framework, NULL);
}
