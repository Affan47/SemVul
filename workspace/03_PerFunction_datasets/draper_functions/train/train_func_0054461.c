h5repack_init(pack_opt_t *options,
                   int verbose)
{
    int k, n;

    HDmemset(options, 0, sizeof(pack_opt_t));
    options->min_comp = 1024;
    options->verbose  = verbose;
    options->layout_g = H5D_LAYOUT_ERROR;

    for ( n = 0; n < H5_REPACK_MAX_NFILTERS; n++)
    {
        options->filter_g[n].filtn  = -1;
        options->filter_g[n].cd_nelmts  = 0;
        for ( k = 0; k < CD_VALUES; k++)
            options->filter_g[n].cd_values[k] = 0;
    }

    return (options_table_init(&(options->op_tbl)));
}
