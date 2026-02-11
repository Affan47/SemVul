cli_cmd_volume_remove_brick_cbk (struct cli_state *state,
                                 struct cli_cmd_word *word, const char **words,
                                 int wordcount)
{
        int                     ret = -1;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        dict_t                  *options = NULL;
        gf_answer_t             answer = GF_ANSWER_NO;
        int                     sent = 0;
        int                     parse_error = 0;
        int                     need_question = 0;

        const char *question = "Removing brick(s) can result in data loss. "
                               "Do you want to Continue?";

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        ret = cli_cmd_volume_remove_brick_parse (words, wordcount, &options,
                                                 &need_question);

        if (ret) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        if (!(state->mode & GLUSTER_MODE_SCRIPT) && need_question) {

                answer = cli_cmd_get_confirmation (state, question);
                if (GF_ANSWER_NO == answer) {
                        ret = 0;
                        goto out;
                }
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_REMOVE_BRICK];

        if (proc->fn) {
                ret = proc->fn (frame, THIS, options);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Volume remove-brick failed");
        }

        if (options)
                dict_unref (options);

        CLI_STACK_DESTROY (frame);

        return ret;

}
