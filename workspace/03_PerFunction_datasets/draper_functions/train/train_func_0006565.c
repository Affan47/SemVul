glusterd_rpc_friend_add (call_frame_t *frame, xlator_t *this,
                         void *data)
{
        gd1_mgmt_friend_req         req      = {{0},};
        int                         ret      = 0;
        glusterd_peerinfo_t        *peerinfo = NULL;
        glusterd_conf_t            *priv     = NULL;
        glusterd_friend_sm_event_t *event    = NULL;
        dict_t                     *vols     = NULL;


        if (!frame || !this || !data) {
                ret = -1;
                goto out;
        }

        event = data;
        priv = this->private;

        GF_ASSERT (priv);

        peerinfo = event->peerinfo;

        ret = glusterd_build_volume_dict (&vols);
        if (ret)
                goto out;

        uuid_copy (req.uuid, MY_UUID);
        req.hostname = peerinfo->hostname;
        req.port = peerinfo->port;

        ret = dict_allocate_and_serialize (vols, &req.vols.vols_val,
                                           &req.vols.vols_len);
        if (ret)
                goto out;

        ret = glusterd_submit_request (peerinfo->rpc, &req, frame, peerinfo->peer,
                                       GLUSTERD_FRIEND_ADD,
                                       NULL, this, glusterd_friend_add_cbk,
                                       (xdrproc_t)xdr_gd1_mgmt_friend_req);


out:
        GF_FREE (req.vols.vols_val);

        if (vols)
                dict_unref (vols);

        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
