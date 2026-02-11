server_unlink (rpcsvc_request_t *req)
{
        server_state_t  *state                  = NULL;
        call_frame_t    *frame                  = NULL;
        gfs3_unlink_req  args                   = {{0,},};
        int              ret                    = -1;

        if (!req)
                return ret;

        args.bname = alloca (req->msg[0].iov_len);

        if (!xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_unlink_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_UNLINK;

        state = CALL_STATE (frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        state->resolve.type   = RESOLVE_MUST;
        state->resolve.bname  = gf_strdup (args.bname);
        memcpy (state->resolve.pargfid, args.pargfid, 16);

        ret = 0;
        resolve_and_resume (frame, server_unlink_resume);
out:
        return ret;
}
