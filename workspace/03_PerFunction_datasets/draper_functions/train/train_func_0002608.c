cli_cmd_uuid_reset_cbk (struct cli_state *state, struct cli_cmd_word *word,
                        const char **words, int wordcount)
{
        int                     ret = -1;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        int                     sent = 0;
        int                     parse_error = 0;
        gf_answer_t             answer = GF_ANSWER_NO;
        char                    *question = NULL;
        cli_local_t             *local = NULL;
        dict_t                  *dict  = NULL;
        xlator_t                *this  = NULL;

        question = "Resetting uuid changes the uuid of local glusterd. "
                   "Do you want to continue?";

        if (wordcount != 3) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_UUID_RESET];

        this = THIS;
        frame = create_frame (this, this->ctx->pool);
        if (!frame)
                goto out;

        dict = dict_new ();
        if (!dict) {
                ret = -1;
                goto out;
        }
        CLI_LOCAL_INIT (local, words, frame, dict);
        answer = cli_cmd_get_confirmation (state, question);

        if (GF_ANSWER_NO == answer) {
                ret = 0;
                goto out;
        }


        if (proc->fn) {
                ret = proc->fn (frame, this, dict);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("uuid reset failed");
        }

        CLI_STACK_DESTROY (frame);

        return ret;
}
