cli_cmd_volume_top_cbk (struct cli_state *state, struct cli_cmd_word *word,
                          const char **words, int wordcount)
{

        int                     ret      = -1;
        rpc_clnt_procedure_t    *proc    = NULL;
        call_frame_t            *frame   = NULL;
        dict_t                  *options = NULL;
        int                     sent     = 0;
        int                     parse_error = 0;

        ret = cli_cmd_volume_top_parse (words, wordcount, &options);

        if (ret) {
                parse_error = 1;
                cli_usage_out (word->pattern);
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_TOP_VOLUME];

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        if (proc->fn) {
                ret = proc->fn (frame, THIS, options);
        }

out:
        if (options)
                dict_unref (options);

        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Volume top failed");
        }

        CLI_STACK_DESTROY (frame);

        return ret;

}
