server_finodelk (rpcsvc_request_t *req)
{
        server_state_t      *state        = NULL;
        call_frame_t        *frame        = NULL;
        gfs3_finodelk_req    args         = {{0,},};
        int                  ret          = -1;

        if (!req)
                return ret;

        args.volume = alloca (4096);
        if (!xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_finodelk_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_FINODELK;

        state = CALL_STATE(frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        state->resolve.type = RESOLVE_EXACT;
        state->volume = gf_strdup (args.volume);
        state->resolve.fd_no = args.fd;
        state->cmd = args.cmd;

        switch (state->cmd) {
        case GF_LK_GETLK:
                state->cmd = F_GETLK;
                break;
        case GF_LK_SETLK:
                state->cmd = F_SETLK;
                break;
        case GF_LK_SETLKW:
                state->cmd = F_SETLKW;
                break;
        }

        state->type = args.type;

        gf_proto_flock_to_flock (&args.flock, &state->flock);

        switch (state->type) {
        case GF_LK_F_RDLCK:
                state->flock.l_type = F_RDLCK;
                break;
        case GF_LK_F_WRLCK:
                state->flock.l_type = F_WRLCK;
                break;
        case GF_LK_F_UNLCK:
                state->flock.l_type = F_UNLCK;
                break;
        }

        ret = 0;
        resolve_and_resume (frame, server_finodelk_resume);
out:
        return ret;
}
