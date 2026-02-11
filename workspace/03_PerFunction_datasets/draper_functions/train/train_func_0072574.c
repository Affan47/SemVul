cli_cmd_volume_heal_cbk (struct cli_state *state, struct cli_cmd_word *word,
                          const char **words, int wordcount)
{
        int                     ret = -1;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        int                     sent = 0;
        int                     parse_error = 0;
        dict_t                  *options = NULL;
        xlator_t                *this = NULL;

        this = THIS;
        frame = create_frame (this, this->ctx->pool);
        if (!frame)
                goto out;

        if (wordcount < 3) {
               cli_usage_out (word->pattern);
               parse_error = 1;
               goto out;
        }

        ret = cli_cmd_volume_heal_options_parse (words, wordcount, &options);
        if (ret) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_HEAL_VOLUME];

        if (proc->fn) {
                ret = proc->fn (frame, THIS, options);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Volume heal failed");
        }

        if (options)
                dict_unref (options);

        CLI_STACK_DESTROY (frame);

        return ret;
}
