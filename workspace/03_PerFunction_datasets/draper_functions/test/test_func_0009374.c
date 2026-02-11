glusterd_cluster_unlock (call_frame_t *frame, xlator_t *this,
                            void *data)
{
        gd1_mgmt_cluster_lock_req       req = {{0},};
        int                             ret = -1;
        glusterd_peerinfo_t             *peerinfo = NULL;
        glusterd_conf_t                 *priv = NULL;
        call_frame_t                    *dummy_frame = NULL;

        if (!this ) {
                ret = -1;
                goto out;
        }
        peerinfo = data;
        priv = this->private;
        GF_ASSERT (priv);

        glusterd_get_uuid (&req.uuid);

        dummy_frame = create_frame (this, this->ctx->pool);
        if (!dummy_frame)
                goto out;

        ret = glusterd_submit_request (peerinfo->rpc, &req, dummy_frame,
                                       peerinfo->mgmt, GLUSTERD_MGMT_CLUSTER_UNLOCK,
                                       NULL,
                                       this, glusterd_cluster_unlock_cbk,
                                       (xdrproc_t)xdr_gd1_mgmt_cluster_unlock_req);
out:
        gf_log (this->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
