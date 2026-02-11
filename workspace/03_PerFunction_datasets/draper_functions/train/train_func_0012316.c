cli_to_glusterd (gf_cli_req *req, call_frame_t *frame,
                 fop_cbk_fn_t cbkfn, xdrproc_t xdrproc, dict_t *dict,
                 int procnum, xlator_t *this, rpc_clnt_prog_t *prog,
                 struct iobref *iobref)
{
        int                ret = 0;
        size_t             len = 0;
        char               *cmd = NULL;
        int                i = 0;
        const char         **words = NULL;
        cli_local_t        *local = NULL;

        if (!this || !frame || !dict) {
                ret = -1;
                goto out;
        }

        if (!frame->local) {
                ret = -1;
                goto out;
        }

        local = frame->local;

        if (!local->words) {
                ret = -1;
                goto out;
        }

        words = local->words;

        while (words[i])
                len += strlen (words[i++]) + 1;

        cmd = GF_CALLOC (1, len, gf_common_mt_char);

        if (!cmd) {
                ret = -1;
                goto out;
        }

        for (i = 0; words[i]; i++) {
                strncat (cmd, words[i], strlen (words[i]));
                if (words[i+1] != NULL)
                        strncat (cmd, " ", strlen (" "));
        }

        cmd [len - 1] = '\0';

        ret = dict_set_dynstr (dict, "cmd-str", cmd);
        if (ret)
                goto out;

        ret = dict_allocate_and_serialize (dict, &(req->dict).dict_val,
                                           &(req->dict).dict_len);

        if (ret < 0) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "failed to get serialized length of dict");
                goto out;
        }

        ret = cli_cmd_submit (req, frame, prog, procnum, iobref, this,
                              cbkfn, (xdrproc_t) xdrproc);

out:
        return ret;

}
