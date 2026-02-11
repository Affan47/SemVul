cli_cmd_volume_clearlocks_cbk (struct cli_state *state,
                               struct cli_cmd_word *word,
                               const char **words, int wordcount)
{
        int                             ret = -1;
        rpc_clnt_procedure_t            *proc = NULL;
        call_frame_t                    *frame = NULL;
        dict_t                          *options = NULL;
        int                             sent = 0;
        int                             parse_error = 0;

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        if (wordcount < 7 || wordcount > 8) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

       ret = cli_cmd_volume_clrlks_opts_parse (words, wordcount, &options);
       if (ret) {
               parse_error = 1;
               gf_log ("cli", GF_LOG_ERROR, "Error parsing "
                       "clear-locks options");
               cli_out ("Error parsing options");
               cli_usage_out (word->pattern);
       }

        ret = dict_set_str (options, "volname", (char *)words[2]);
        if (ret)
                goto out;

        ret = dict_set_str (options, "path", (char *)words[3]);
        if (ret)
                goto out;

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_CLRLOCKS_VOLUME];
        if (proc->fn) {
                ret = proc->fn (frame, THIS, options);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error = 0))
                        cli_out ("Volume clear-locks failed");
        }

        CLI_STACK_DESTROY (frame);

        return ret;
}
