free_gic_opt_ext_preauth_data(krb5_context context,
                              krb5_gic_opt_ext *opte)
{
    int i;

    if (NULL == opte || !gic_opt_is_extended(opte))
        return;
    if (NULL == opte->opt_private || NULL == opte->opt_private->preauth_data)
        return;

    for (i = 0; i < opte->opt_private->num_preauth_data; i++) {
        if (opte->opt_private->preauth_data[i].attr != NULL)
            free(opte->opt_private->preauth_data[i].attr);
        if (opte->opt_private->preauth_data[i].value != NULL)
            free(opte->opt_private->preauth_data[i].value);
    }
    free(opte->opt_private->preauth_data);
    opte->opt_private->preauth_data = NULL;
    opte->opt_private->num_preauth_data = 0;
}
