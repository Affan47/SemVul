add_server_entry(krb5_context context, const char *name)
{
    krb5_ldap_context *lctx = context->dal_handle->db_context;
    krb5_ldap_server_info **sp, **list, *server;
    size_t count = 0;


    for (sp = lctx->server_info_list; sp != NULL && *sp != NULL; sp++)
        count++;
    list = realloc(lctx->server_info_list, (count + 2) * sizeof(*list));
    if (list == NULL)
        return ENOMEM;
    lctx->server_info_list = list;

    server = calloc(1, sizeof(krb5_ldap_server_info));
    if (server == NULL)
        return ENOMEM;
    server->server_status = NOTSET;
    server->server_name = strdup(name);
    if (server->server_name == NULL) {
        free(server);
        return ENOMEM;
    }
    list[count] = server;
    list[count + 1] = NULL;
    return 0;
}
