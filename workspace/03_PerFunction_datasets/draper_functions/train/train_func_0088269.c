rtree_hier_tree(krb5_context context,
                const krb5_data *client,
                const krb5_data *server,
                krb5_principal **rettree,
                int sep)
{
    krb5_error_code retval;
    krb5_data *realms;
    const krb5_data *dstrealm, *srcrealm;
    krb5_principal *tree, *pprinc;
    size_t nrealms, nprincs, i;

    *rettree = NULL;
    retval = rtree_hier_realms(context, client, server,
                               &realms, &nrealms, sep);
    if (retval)
        return retval;
    nprincs = nrealms;
    pprinc = tree = calloc(nprincs + 1, sizeof(krb5_principal));
    if (tree == NULL) {
        retval = ENOMEM;
        goto error;
    }
    for (i = 0; i < nrealms; i++)
        tree[i] = NULL;
    srcrealm = client;
    for (i = 0; i < nrealms; i++) {
        dstrealm = &realms[i];
        retval = krb5int_tgtname(context, dstrealm, srcrealm, pprinc++);
        if (retval) goto error;
        srcrealm = dstrealm;
    }
    *rettree = tree;
    free_realmlist(context, realms, nrealms);
    return 0;
error:
    while (pprinc != NULL && pprinc > tree) {
        krb5_free_principal(context, *--pprinc);
        *pprinc = NULL;
    }
    free_realmlist(context, realms, nrealms);
    free(tree);
    return retval;
}
