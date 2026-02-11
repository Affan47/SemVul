glusterd3_1_brick_op (call_frame_t *frame, xlator_t *this,
                      void *data)
{
        gd1_mgmt_brick_op_req           *req = NULL;
        int                             ret = 0;
        glusterd_conf_t                 *priv = NULL;
        call_frame_t                    *dummy_frame = NULL;
        char                            *op_errstr = NULL;
        int                             pending_bricks = 0;
        glusterd_pending_node_t         *pending_node;
        glusterd_req_ctx_t               *req_ctx = NULL;
        struct rpc_clnt                 *rpc = NULL;

        if (!this) {
                ret = -1;
                goto out;
        }
        priv = this->private;
        GF_ASSERT (priv);

        req_ctx = data;
        GF_ASSERT (req_ctx);
        INIT_LIST_HEAD (&opinfo.pending_bricks);
        ret = glusterd_op_bricks_select (req_ctx->op, req_ctx->dict, &op_errstr);

        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Brick Op failed");
                opinfo.op_errstr = op_errstr;
                goto out;
        }

        list_for_each_entry (pending_node, &opinfo.pending_bricks, list) {
                dummy_frame = create_frame (this, this->ctx->pool);
                if (!dummy_frame)
                        continue;

                ret = glusterd_brick_op_build_payload (req_ctx->op,
                                                       pending_node->node,
                                                       (gd1_mgmt_brick_op_req **)&req,
                                                       req_ctx->dict);
                if (ret)
                        goto out;

                dummy_frame->local = data;
                dummy_frame->cookie = pending_node;

                rpc = glusterd_pending_node_get_rpc (pending_node);
                if (!rpc) {
                        ret = -1;
                        gf_log (this->name, GF_LOG_ERROR, "Brick Op failed "
                                "due to rpc failure.");
                        goto out;
                }

                ret = glusterd_submit_request (rpc, req, dummy_frame,
                                               priv->gfs_mgmt,
                                               req->op, NULL,
                                               this, glusterd3_1_brick_op_cbk,
                                               (xdrproc_t)xdr_gd1_mgmt_brick_op_req);
                if (req) {
                        if (req->input.input_val)
                                GF_FREE (req->input.input_val);
                        GF_FREE (req);
                        req = NULL;
                }
                if (!ret)
                        pending_bricks++;
        }

        gf_log ("glusterd", GF_LOG_DEBUG, "Sent op req to %d bricks",
                pending_bricks);
        opinfo.brick_pending_count = pending_bricks;

out:
        if (ret) {
                glusterd_op_sm_inject_event (GD_OP_EVENT_RCVD_RJT, data);
                opinfo.op_ret = ret;
        }
        gf_log ("glusterd", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
