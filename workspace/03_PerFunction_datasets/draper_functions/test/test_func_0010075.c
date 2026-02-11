cli_cmd_quota_cbk (struct cli_state *state, struct cli_cmd_word *word,
                   const char **words, int wordcount)
{

        int                      ret       = 0;
        int                      parse_err = 0;
        int32_t                  type      = 0;
        rpc_clnt_procedure_t    *proc      = NULL;
        call_frame_t            *frame     = NULL;
        dict_t                  *options   = NULL;
        gf_answer_t              answer    = GF_ANSWER_NO;
        const char *question = "Disabling quota will delete all the quota "
                               "configuration. Do you want to continue?";

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_QUOTA];
        if (proc == NULL) {
                ret = -1;
                goto out;
        }

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame) {
                ret = -1;
                goto out;
        }

        ret = cli_cmd_quota_parse (words, wordcount, &options);
        if (ret < 0) {
                cli_usage_out (word->pattern);
                parse_err = 1;
                goto out;
        } else if (dict_get_int32 (options, "type", &type) == 0 &&
                   type == GF_QUOTA_OPTION_TYPE_DISABLE) {
                answer = cli_cmd_get_confirmation (state, question);
                if (answer == GF_ANSWER_NO)
                        goto out;
        }

        if (proc->fn)
                ret = proc->fn (frame, THIS, options);

out:
        if (options)
                dict_unref (options);

        if (ret && parse_err == 0)
                cli_out ("Quota command failed");

        CLI_STACK_DESTROY (frame);

        return ret;

}
