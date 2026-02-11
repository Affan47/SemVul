fetion_config_save_account(fetion_account *account)
{
    const gchar *body;
    gchar       *account_dir;
    gchar       *account_name;
    gchar       *port;
    xmlnode     *root;
    xmlnode     *node;
    xmlnode     *new;

    g_return_if_fail(account != NULL);

    if (!(account_dir = fetion_get_config_dir(account))) {
        hybrid_debug_error("fetion", "get config dir error.");
        return;
    }

    account_name = g_strdup_printf("%s/account.xml", account_dir);

    body = "<root></root>";

    root = xmlnode_root(body, strlen(body));

    node = xmlnode_new_child(root, "account");

    xmlnode_new_prop(node, "personal-version", account->personal_version);
    xmlnode_new_prop(node, "contact-version", account->contact_list_version);
    xmlnode_new_prop(node, "custom-version", account->custom_config_version);

    node = xmlnode_new_child(root, "custom-config");
    xmlnode_set_content(node, account->custom_config);

    node = xmlnode_new_child(root, "config");
    xmlnode_new_prop(node, "servers-version", account->cfg_server_version);
    xmlnode_new_prop(node, "parameters-version", account->cfg_param_version);
    xmlnode_new_prop(node, "hints-version", account->cfg_hint_version);
    xmlnode_new_prop(node, "client-version", account->cfg_client_version);

    port = g_strdup_printf("%d", account->sipc_proxy_port);
    new = xmlnode_new_child(node, "sipc-server");
    xmlnode_new_prop(new, "host", account->sipc_proxy_ip);
    xmlnode_new_prop(new, "port", port);
    g_free(port);

    new = xmlnode_new_child(node, "portrait-server");
    xmlnode_new_prop(new, "name", account->portrait_host_name);
    xmlnode_new_prop(new, "path", account->portrait_host_path);

    xmlnode_save_file(root, account_name);
    xmlnode_free(root);
    g_free(account_name);
}
