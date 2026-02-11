glusterd_handle_commit_op (rpcsvc_request_t *req)
{
        int32_t                         ret = -1;
        glusterd_req_ctx_t              *req_ctx = NULL;
        gd1_mgmt_commit_op_req          op_req = {{0},};
        glusterd_peerinfo_t             *peerinfo = NULL;

        GF_ASSERT (req);

        if (!xdr_to_generic (req->msg[0], &op_req, (xdrproc_t)xdr_gd1_mgmt_commit_op_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        if (glusterd_friend_find_by_uuid (op_req.uuid, &peerinfo)) {
                gf_log (THIS->name, GF_LOG_WARNING, "%s doesn't "
                        "belong to the cluster. Ignoring request.",
                        uuid_utoa (op_req.uuid));
                ret = -1;
                goto out;
        }


        GF_ASSERT (sizeof (gd1_mgmt_commit_op_req) == sizeof (gd1_mgmt_stage_op_req));
        ret = glusterd_req_ctx_create (req, op_req.op, op_req.uuid,
                                       op_req.buf.buf_val, op_req.buf.buf_len,
                                       gf_gld_mt_op_commit_ctx_t, &req_ctx);
        if (ret)
                goto out;

        ret = glusterd_op_sm_inject_event (GD_OP_EVENT_COMMIT_OP, req_ctx);
        if (ret)
                goto out;
        ret = glusterd_op_init_ctx (op_req.op);

out:
        if (op_req.buf.buf_val)
                free (op_req.buf.buf_val);
        glusterd_friend_sm ();
        glusterd_op_sm ();
        return ret;
}
