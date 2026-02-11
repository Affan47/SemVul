cli_cmd_peer_deprobe_cbk (struct cli_state *state, struct cli_cmd_word *word,
                          const char **words, int wordcount)
{
        int                   ret   = -1;
        rpc_clnt_procedure_t *proc  = NULL;
        call_frame_t         *frame = NULL;
        dict_t               *dict  = NULL;
        int                  flags = 0;
        int                  sent = 0;
        int                  parse_error = 0;

        if ((wordcount < 3) || (wordcount > 4)) {
                cli_usage_out (word->pattern);
                parse_error = 1;
                goto out;
        }

        proc = &cli_rpc_prog->proctable[GLUSTER_CLI_DEPROBE];

        frame = create_frame (THIS, THIS->ctx->pool);
        if (!frame)
                goto out;

        dict = dict_new ();

        ret = dict_set_str (dict, "hostname", (char *)words[2]);
        if (ret)
                goto out;


        if (wordcount == 4) {
                if (!strcmp("force", words[3]))
                        flags |= GF_CLI_FLAG_OP_FORCE;
                else {
                        ret = -1;
                        cli_usage_out (word->pattern);
                        parse_error = 1;
                        goto out;
                }
        }
        ret = dict_set_int32 (dict, "flags", flags);
        if (ret)
                goto out;

        if (proc->fn) {
                ret = proc->fn (frame, THIS, dict);
        }

out:
        if (ret) {
                cli_cmd_sent_status_get (&sent);
                if ((sent == 0) && (parse_error == 0))
                        cli_out ("Peer detach failed");
        }

        CLI_STACK_DESTROY (frame);

        return ret;
}
