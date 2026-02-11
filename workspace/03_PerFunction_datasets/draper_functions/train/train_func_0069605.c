cmd_mount(cmd_parms *cmd, void *dummy, const char *path, const char *addr)
{
    int n;
    apr_status_t rv;
    char *scope_id = NULL;
    scgi_server_cfg *scfg = our_sconfig(cmd->server);
    mount_entry *new = apr_array_push(scfg->mounts);
    n = strlen(path);
    while (n > 0 && path[n-1] == '/') {
        n--;
    }
    new->path = apr_pstrndup(cmd->pool, path, n);
    rv = apr_parse_addr_port(&new->addr, &scope_id, &new->port, addr,
                             cmd->pool);
    if (rv)
        return "error parsing address:port string";
    return NULL;
}
