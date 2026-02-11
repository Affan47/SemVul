print_princ(kdbe_princ_t *princ)
{
    int i, len;
    kdbe_data_t *data;

    print_str("realm", &princ->k_realm);

    len = princ->k_components.k_components_len;
    data = princ->k_components.k_components_val;

    for (i = 0; i < len; i++, data++) {

        print_data("princ", data);
    }
}
