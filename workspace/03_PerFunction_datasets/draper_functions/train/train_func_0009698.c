server_fsetattr (rpcsvc_request_t *req)
{
        server_state_t    *state = NULL;
        call_frame_t      *frame = NULL;
        gfs3_fsetattr_req  args  = {0,};
        int                ret   = -1;
        int                op_errno = 0;

        if (!req)
                return ret;

        if (!xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_fsetattr_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_FSETATTR;

        state = CALL_STATE (frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        state->resolve.type   = RESOLVE_MUST;
        state->resolve.fd_no  = args.fd;

        gf_stat_to_iatt (&args.stbuf, &state->stbuf);
        state->valid = args.valid;

        GF_PROTOCOL_DICT_UNSERIALIZE (state->conn->bound_xl, state->xdata,
                                      (args.xdata.xdata_val),
                                      (args.xdata.xdata_len), ret,
                                      op_errno, out);

        ret = 0;
        resolve_and_resume (frame, server_fsetattr_resume);

out:
        if (args.xdata.xdata_val)
                free (args.xdata.xdata_val);

        if (op_errno)
                req->rpc_err = GARBAGE_ARGS;

        return ret;
}
