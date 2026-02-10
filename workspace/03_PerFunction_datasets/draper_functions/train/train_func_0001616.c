cli_cmd_volume_gsync_set_cbk (struct cli_state *state, struct cli_cmd_word *word,
                              const char **words, int wordcount)
{
        int                      ret     = 0;
        int                      parse_err = 0;
        dict_t                  *options = NULL;
        rpc_clnt_procedure_t    *proc    = NULL;
        call_frame_t            *frame   = NULL;
        cli_local_t             *local   = NULL;

        proc = &cli_rpc_prog->proctable [GLUSTER_CLI_GSYNC_SET];
        if (proc == NULL) {
                ret = -1;
                goto out;
        }

        frame = create_frame (THIS, THIS->ctx->pool);
        if (frame == NULL) {
                ret = -1;
                goto out;
        }

        ret = cli_cmd_gsync_set_parse (words, wordcount, &options);
        if (ret) {
                cli_usage_out (word->pattern);
                parse_err = 1;
                goto out;
        }

        CLI_LOCAL_INIT (local, words, frame, options);

        if (proc->fn)
                ret = proc->fn (frame, THIS, options);

out:
        if (ret && parse_err == 0)
                cli_out (GEOREP" command failed");

        CLI_STACK_DESTROY (frame);

        return ret;
}
