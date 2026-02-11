glusterd_ac_friend_probe (glusterd_friend_sm_event_t *event, void *ctx)
{
        int                     ret = -1;
        rpc_clnt_procedure_t    *proc = NULL;
        call_frame_t            *frame = NULL;
        glusterd_conf_t         *conf = NULL;
        xlator_t                *this = NULL;
        glusterd_probe_ctx_t    *probe_ctx = NULL;
        glusterd_peerinfo_t     *peerinfo = NULL;
        dict_t                  *dict = NULL;

        GF_ASSERT (ctx);

        probe_ctx = ctx;

        this = THIS;

        GF_ASSERT (this);

        conf = this->private;

        GF_ASSERT (conf);

        ret = glusterd_friend_find (NULL, probe_ctx->hostname, &peerinfo);
        if (ret) {

                GF_ASSERT (0);
                goto out;
        }

        if (!peerinfo->peer)
                goto out;
        proc = &peerinfo->peer->proctable[GLUSTERD_PROBE_QUERY];
        if (proc->fn) {
                frame = create_frame (this, this->ctx->pool);
                if (!frame) {
                        goto out;
                }
                frame->local = ctx;
                dict = dict_new ();
                if (!dict)
                        goto out;
                ret = dict_set_str (dict, "hostname", probe_ctx->hostname);
                if (ret)
                        goto out;

                ret = dict_set_int32 (dict, "port", probe_ctx->port);
                if (ret)
                        goto out;

                ret = dict_set_static_ptr (dict, "peerinfo", peerinfo);
                if (ret) {
                        gf_log ("", GF_LOG_ERROR, "failed to set peerinfo");
                        goto out;
                }

                ret = proc->fn (frame, this, dict);
                if (ret)
                        goto out;

        }


out:
        if (dict)
                dict_unref (dict);
        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);

        return ret;
}
