include_cmd(include_ctx_t *ctx, ap_filter_t *f,
                       apr_bucket_brigade *bb, char *command)
{
    char **env;
    int sd;
    int retval;
    apr_file_t *tempsock = NULL;
    request_rec *r = f->r;
    cgid_server_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &cgid_module);
    struct cleanup_script_info *info;

    add_ssi_vars(r);
    env = ap_create_environment(r->pool, r->subprocess_env);

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    send_req(sd, r, command, env, SSI_REQ);

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->r = r;
    info->conn_id = r->connection->id;
    info->conf = conf;


    apr_pool_cleanup_register(r->pool, info,
                              cleanup_script,
                              apr_pool_cleanup_null);


    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    apr_pool_cleanup_kill(r->pool, (void *)((long)sd), close_unix_socket);

    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(tempsock,
                            f->c->bucket_alloc));
    ctx->flush_now = 1;

    return APR_SUCCESS;
}
