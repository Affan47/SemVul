cli_cmd_volume_status_cbk (struct cli_state *state,
                              struct cli_cmd_word *word,
                              const char **words, int wordcount)
{
        int                   ret         = -1;
        rpc_clnt_procedure_t *proc        = NULL;
        call_frame_t         *frame       = NULL;
        dict_t               *dict        = NULL;

        if (wordcount != 3) {
                cli_usage_out (word->pattern);
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_STATUS_VOLUME];

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        ret = cli_cmd_volume_status_parse (words, wordcount, &dict);
        if (ret)
                goto out;

        if (proc->fn)
                ret = proc->fn (frame, THIS, dict);

 out:
        return ret;
}
