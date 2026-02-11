_gd_syncop_stage_op_cbk (struct rpc_req *req, struct iovec *iov,
                         int count, void *myframe)
{
        int                         ret         = -1;
        gd1_mgmt_stage_op_rsp       rsp         = {{0},};
        struct syncargs             *args       = NULL;
        xlator_t                    *this       = NULL;
        dict_t                      *rsp_dict   = NULL;
        call_frame_t                *frame      = NULL;

        this  = THIS;
        frame = myframe;
        args  = frame->local;
        frame->local = NULL;

        if (-1 == req->rpc_status) {
                args->op_ret   = -1;
                args->op_errno = ENOTCONN;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_stage_op_rsp);
        if (ret < 0)
                goto out;

        if (rsp.dict.dict_len) {

                rsp_dict  = dict_new ();

                ret = dict_unserialize (rsp.dict.dict_val,
                                        rsp.dict.dict_len,
                                        &rsp_dict);
                if (ret < 0) {
                        GF_FREE (rsp.dict.dict_val);
                        goto out;
                } else {
                        rsp_dict->extra_stdfree = rsp.dict.dict_val;
                }
        }

        gd_collate_errors (args, rsp.op_ret, rsp.op_errno, rsp.op_errstr);
        uuid_copy (args->uuid, rsp.uuid);
        if (rsp.op == GD_OP_REPLACE_BRICK) {
                pthread_mutex_lock (&args->lock_dict);
                {
                        ret = glusterd_syncop_aggr_rsp_dict (rsp.op, args->dict,
                                                             rsp_dict);
                        if (ret)
                                gf_log (this->name, GF_LOG_ERROR, "%s",
                                        "Failed to aggregate response from "
                                        " node/brick");
                }
                pthread_mutex_unlock (&args->lock_dict);
        }

out:
        if (rsp_dict)
                dict_unref (rsp_dict);

        STACK_DESTROY (frame->root);
        synctask_barrier_wake(args);
        return 0;
}
