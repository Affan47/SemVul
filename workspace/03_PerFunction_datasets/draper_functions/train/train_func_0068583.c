krb5_free_tgt_creds(krb5_context context, krb5_creds **tgts)
{
    register krb5_creds **tgtpp;
    if (tgts == NULL)
        return;
    for (tgtpp = tgts; *tgtpp; tgtpp++)
        krb5_free_creds(context, *tgtpp);
    free(tgts);
}
