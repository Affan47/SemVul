cli_cmd_uuid_get_cbk (struct cli_state *state, struct cli_cmd_word *word,
                      const char **words, int wordcount)
{
        int                     ret = -1;
        int                     sent = 0;
        int                     parse_error = 0;
        dict_t                  *dict  = NULL;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        cli_local_t             *local = NULL;
        xlator_t                *this  = NULL;

        this = THIS;
        if (wordcount != 3) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_UUID_GET];
        frame = create_frame (this, this->ctx->pool);
        if (!frame)
                goto out;

        dict = dict_new ();
        if (!dict)
                goto out;

        CLI_LOCAL_INIT (local, words, frame, dict);
        if (proc->fn)
                ret = proc->fn (frame, this, dict);

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("uuid get failed");
        }

        if (dict)
                dict_unref (dict);

        CLI_STACK_DESTROY (frame);
        return ret;
}
