krb5_authdata_export_authdata(krb5_context kcontext,
                              krb5_authdata_context context,
                              krb5_flags flags,
                              krb5_authdata ***pauthdata)
{
    int i;
    krb5_error_code code = 0;
    krb5_authdata **authdata = NULL;
    unsigned int len = 0;

    *pauthdata = NULL;

    for (i = 0; i < context->n_modules; i++) {
        struct _krb5_authdata_context_module *module = &context->modules[i];
        krb5_authdata **authdata2 = NULL;
        int j;

        if ((module->flags & flags) == 0)
            continue;

        if (module->ftable->export_authdata == NULL)
            continue;

        code = (*module->ftable->export_authdata)(kcontext,
                                                  context,
                                                  module->plugin_context,
                                                  *(module->request_context_pp),
                                                  flags,
                                                  &authdata2);
        if (code == ENOENT)
            code = 0;
        else if (code != 0)
            break;

        if (authdata2 == NULL)
            continue;

        for (j = 0; authdata2[j] != NULL; j++)
            ;

        authdata = realloc(authdata, (len + j + 1) * sizeof(krb5_authdata *));
        if (authdata == NULL)
            return ENOMEM;

        memcpy(&authdata[len], authdata2, j * sizeof(krb5_authdata *));
        free(authdata2);

        len += j;
    }

    if (authdata != NULL)
        authdata[len] = NULL;

    if (code != 0) {
        krb5_free_authdata(kcontext, authdata);
        return code;
    }

    *pauthdata = authdata;

    return 0;
}
