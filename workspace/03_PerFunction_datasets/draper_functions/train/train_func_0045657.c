glusterd_peer_rpc_notify (struct rpc_clnt *rpc, void *mydata,
                          rpc_clnt_event_t event,
                          void *data)
{
        xlator_t             *this        = NULL;
        glusterd_conf_t      *conf        = NULL;
        int                   ret         = 0;
        glusterd_peerinfo_t  *peerinfo    = NULL;
        glusterd_peerctx_t   *peerctx     = NULL;
        uuid_t                owner       = {0,};
        uuid_t               *peer_uuid   = NULL;

        peerctx = mydata;
        if (!peerctx)
                return 0;

        peerinfo = peerctx->peerinfo;
        this = THIS;
        conf = this->private;

        switch (event) {
        case RPC_CLNT_CONNECT:
        {
                gf_log (this->name, GF_LOG_DEBUG, "got RPC_CLNT_CONNECT");
                peerinfo->connected = 1;

                ret = glusterd_peer_handshake (this, rpc, peerctx);
                if (ret)
                        gf_log ("", GF_LOG_ERROR, "glusterd handshake failed");
                break;
        }

        case RPC_CLNT_DISCONNECT:
        {
                gf_log (this->name, GF_LOG_DEBUG, "got RPC_CLNT_DISCONNECT %d",
                        peerinfo->state.state);

                peerinfo->connected = 0;


                glusterd_get_lock_owner (&owner);
                if (!uuid_compare (conf->uuid, owner)) {
                        ret = glusterd_op_sm_inject_event (GD_OP_EVENT_START_UNLOCK,
                                                           NULL);
                        if (ret)
                                gf_log (this->name, GF_LOG_ERROR, "Unable"
                                        " to enqueue cluster unlock event");
                        break;
                }

                peer_uuid = GF_CALLOC (1, sizeof (*peer_uuid), gf_common_mt_char);
                if (!peer_uuid) {
                        ret = -1;
                        break;
                }

                uuid_copy (*peer_uuid, peerinfo->uuid);
                ret = glusterd_op_sm_inject_event (GD_OP_EVENT_LOCAL_UNLOCK_NO_RESP,
                                                   peer_uuid);
                if (ret)
                        gf_log (this->name, GF_LOG_ERROR, "Unable"
                                " to enque local lock flush event.");


                if (peerinfo->state.state == GD_FRIEND_STATE_DEFAULT)  {


                        glusterd_friend_remove_notify (peerinfo,
                                                       peerctx->args.req);
                }


                break;
        }
        default:
                gf_log (this->name, GF_LOG_TRACE,
                        "got some other RPC event %d", event);
                ret = 0;
                break;
        }

        glusterd_friend_sm ();
        glusterd_op_sm ();
        return ret;
}
