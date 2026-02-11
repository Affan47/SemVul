pkinit_init_plg_opts(pkinit_plg_opts **plgopts)
{
    krb5_error_code retval = ENOMEM;
    pkinit_plg_opts *opts = NULL;

    *plgopts = NULL;
    opts = calloc(1, sizeof(pkinit_plg_opts));
    if (opts == NULL)
        return retval;

    opts->require_eku = 1;
    opts->accept_secondary_eku = 0;
    opts->dh_or_rsa = DH_PROTOCOL;
    opts->allow_upn = 0;
    opts->require_crl_checking = 0;

    opts->dh_min_bits = PKINIT_DEFAULT_DH_MIN_BITS;

    *plgopts = opts;

    return 0;
}
