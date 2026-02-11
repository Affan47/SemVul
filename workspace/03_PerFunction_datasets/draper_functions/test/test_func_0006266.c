cli_cmd_volume_info_cbk (struct cli_state *state, struct cli_cmd_word *word,
                         const char **words, int wordcount)
{
        int                             ret = -1;
        rpc_clnt_procedure_t            *proc = NULL;
        call_frame_t                    *frame = NULL;
        cli_cmd_volume_get_ctx_t        ctx = {0,};
        cli_local_t                     *local = NULL;
        int                             sent = 0;
        int                             parse_error = 0;

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_GET_VOLUME];

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        if ((wordcount == 2)  || (wordcount == 3 &&
                                  !strcmp (words[2], "all"))) {
                ctx.flags = GF_CLI_GET_NEXT_VOLUME;
                proc = &cli_rpc_prog->proctable[GLUSTER_CLI_GET_NEXT_VOLUME];
        } else if (wordcount == 3) {
                ctx.flags = GF_CLI_GET_VOLUME;
                ctx.volname = (char *)words[2];
                if (strlen (ctx.volname) > 1024) {
                        cli_out ("Invalid volume name");
                        goto out;
                }
                proc = &cli_rpc_prog->proctable[GLUSTER_CLI_GET_VOLUME];
        } else {
                cli_usage_out (word->pattern);
                parse_error = 1;
                return -1;
        }

        local = cli_local_get ();

        if (!local)
                goto out;

        local->get_vol.flags = ctx.flags;
        if (ctx.volname)
                local->get_vol.volname = gf_strdup (ctx.volname);

        frame->local = local;

        if (proc->fn) {
                ret = proc->fn (frame, THIS, &ctx);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Getting Volume information failed!");
        }

        CLI_STACK_DESTROY (frame);

        return ret;

}
