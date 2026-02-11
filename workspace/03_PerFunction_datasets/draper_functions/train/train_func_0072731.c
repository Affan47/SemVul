glusterd_op_ac_brick_op_failed (glusterd_op_sm_event_t *event, void *ctx)
{
        int                     ret = 0;
        glusterd_op_brick_rsp_ctx_t *ev_ctx = NULL;
        gf_boolean_t                free_errstr = _gf_false;
        xlator_t                    *this = NULL;

        this = THIS;
        GF_ASSERT (this);

        GF_ASSERT (event);
        GF_ASSERT (ctx);
        ev_ctx = ctx;

        ret = glusterd_remove_pending_entry (&opinfo.pending_bricks, ev_ctx->pending_node->node);
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, "unknown response received ");
                ret = -1;
                free_errstr = _gf_true;
                goto out;
        }
        if (opinfo.brick_pending_count > 0)
                opinfo.brick_pending_count--;
        if (opinfo.op_ret == 0)
                opinfo.op_ret = ev_ctx->op_ret;

        if (opinfo.op_errstr == NULL)
                opinfo.op_errstr = ev_ctx->op_errstr;
        else
                free_errstr = _gf_true;

        if (opinfo.brick_pending_count > 0)
                goto out;

        ret = glusterd_op_sm_inject_event (GD_OP_EVENT_ALL_ACK, ev_ctx->commit_ctx);

out:
        if (ev_ctx->rsp_dict)
                dict_unref (ev_ctx->rsp_dict);
        if (free_errstr && ev_ctx->op_errstr)
                GF_FREE (ev_ctx->op_errstr);
        GF_FREE (ctx);
        gf_log (this->name, GF_LOG_DEBUG, "Returning %d", ret);

        return ret;
}
