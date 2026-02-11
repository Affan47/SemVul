glusterd_ac_send_friend_update (glusterd_friend_sm_event_t *event, void *ctx)
{
        int                           ret               = 0;
        glusterd_peerinfo_t          *cur_peerinfo      = NULL;
        glusterd_peerinfo_t          *peerinfo          = NULL;
        rpc_clnt_procedure_t         *proc              = NULL;
        xlator_t                     *this              = NULL;
        glusterd_friend_update_ctx_t  ev_ctx            = {{0}};
        glusterd_conf_t              *priv              = NULL;
        dict_t                       *friends           = NULL;
        char                          key[100]          = {0,};
        char                         *dup_buf           = NULL;
        int32_t                       count             = 0;

        GF_ASSERT (event);
        cur_peerinfo = event->peerinfo;

        this = THIS;
        priv = this->private;

        GF_ASSERT (priv);

        ev_ctx.op = GD_FRIEND_UPDATE_ADD;

        friends = dict_new ();
        if (!friends)
                goto out;

        snprintf (key, sizeof (key), "op");
        ret = dict_set_int32 (friends, key, ev_ctx.op);
        if (ret)
                goto out;

        list_for_each_entry (peerinfo, &priv->peers, uuid_list) {
                if (!glusterd_should_update_peer (peerinfo, cur_peerinfo))
                        continue;

                count++;
                snprintf (key, sizeof (key), "friend%d.uuid", count);
                dup_buf = gf_strdup (uuid_utoa (peerinfo->uuid));
                ret = dict_set_dynstr (friends, key, dup_buf);
                if (ret)
                        goto out;
                snprintf (key, sizeof (key), "friend%d.hostname", count);
                ret = dict_set_str (friends, key, peerinfo->hostname);
                if (ret)
                        goto out;
                gf_log ("", GF_LOG_INFO, "Added uuid: %s, host: %s",
                        dup_buf, peerinfo->hostname);
        }

        ret = dict_set_int32 (friends, "count", count);
        if (ret)
                goto out;

        list_for_each_entry (peerinfo, &priv->peers, uuid_list) {
                if (!peerinfo->connected || !peerinfo->peer)
                        continue;

                if (!glusterd_should_update_peer (peerinfo, cur_peerinfo))
                        continue;

                ret = dict_set_static_ptr (friends, "peerinfo", peerinfo);
                if (ret) {
                        gf_log ("", GF_LOG_ERROR, "failed to set peerinfo");
                        goto out;
                }

                proc = &peerinfo->peer->proctable[GLUSTERD_FRIEND_UPDATE];
                if (proc->fn) {
                        ret = proc->fn (NULL, this, friends);
                }
        }

        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);

out:
        if (friends)
                dict_unref (friends);

        return ret;
}
