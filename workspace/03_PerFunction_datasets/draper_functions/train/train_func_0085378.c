server3_3_readdir (rpcsvc_request_t *req)
{
        server_state_t      *state        = NULL;
        call_frame_t        *frame        = NULL;
        gfs3_readdir_req     args         = {{0,},};
        size_t               headers_size = 0;
        int                  ret          = -1;
        int                  op_errno = 0;

        if (!req)
                return ret;

        ret = xdr_to_generic (req->msg[0], &args,
                              (xdrproc_t)xdr_gfs3_readdir_req);
        if (ret < 0) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_READDIR;

        state = CALL_STATE(frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }


        headers_size = sizeof (struct rpc_msg) + sizeof (gfs3_readdir_rsp);
        if ((frame->this->ctx->page_size < args.size)
            || ((frame->this->ctx->page_size - args.size) < headers_size)) {
                state->size = frame->this->ctx->page_size - headers_size;
        } else {
                state->size   = args.size;
        }

        state->resolve.type = RESOLVE_MUST;
        state->resolve.fd_no = args.fd;
        state->offset = args.offset;
        memcpy (state->resolve.gfid, args.gfid, 16);

        GF_PROTOCOL_DICT_UNSERIALIZE (state->conn->bound_xl, state->xdata,
                                      (args.xdata.xdata_val),
                                      (args.xdata.xdata_len), ret,
                                      op_errno, out);

        ret = 0;
        resolve_and_resume (frame, server_readdir_resume);
out:
        free (args.xdata.xdata_val);

        if (op_errno)
                req->rpc_err = GARBAGE_ARGS;

        return ret;
}
