data_finalize(void)
{
    int i;

    for (i = 0 ; i <= parse_options_idx ; ++i) {
        options_data_free(&(options_data[i]));
    }
    free(options_data);

    return OPAL_SUCCESS;
}
