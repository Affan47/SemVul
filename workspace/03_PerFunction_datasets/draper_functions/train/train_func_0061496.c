cli_cmd_volume_reset_cbk (struct cli_state *state, struct cli_cmd_word *word,
                          const char **words, int wordcount)
{
        int                     sent = 0;
        int                     parse_error = 0;

        int                     ret = -1;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        dict_t                  *options = NULL;

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_RESET_VOLUME];

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        ret = cli_cmd_volume_reset_parse (words, wordcount, &options);

        if (ret) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        if (proc->fn) {
                ret = proc->fn (frame, THIS, options);
        }

out:
        if (options)
                dict_unref (options);

        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Volume reset failed");
        }

        return ret;

}
