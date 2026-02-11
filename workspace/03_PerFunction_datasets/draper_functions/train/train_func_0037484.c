krb5_get_init_creds_opt_free(krb5_context context,
                             krb5_get_init_creds_opt *opt)
{
    krb5_gic_opt_ext *opte;

    if (NULL == opt)
        return;


    if (!gic_opt_is_extended(opt))
        return;

    opte = (krb5_gic_opt_ext *)opt;
    if (opte->opt_private)
        gic_opte_private_free(context, opte);

    free(opte);
}
