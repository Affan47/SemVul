server3_3_lk (rpcsvc_request_t *req)
{
        server_state_t      *state = NULL;
        call_frame_t        *frame = NULL;
        gfs3_lk_req          args  = {{0,},};
        int                  ret   = -1;
        int                  op_errno = 0;

        if (!req)
                return ret;

        ret = xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_lk_req);
        if (ret < 0) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_LK;

        state = CALL_STATE (frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        state->resolve.fd_no = args.fd;
        state->cmd =  args.cmd;
        state->type = args.type;
        memcpy (state->resolve.gfid, args.gfid, 16);

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
        case GF_LK_RESLK_LCK:
                state->cmd = F_RESLK_LCK;
                break;
        case GF_LK_RESLK_LCKW:
                state->cmd = F_RESLK_LCKW;
                break;
        case GF_LK_RESLK_UNLCK:
                state->cmd = F_RESLK_UNLCK;
                break;
        case GF_LK_GETLK_FD:
                state->cmd = F_GETLK_FD;
                break;

        }


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
        default:
                gf_log (state->conn->bound_xl->name, GF_LOG_ERROR,
                        "fd - %"PRId64" (%s): Unknown lock type: %"PRId32"!",
                        state->resolve.fd_no,
                        uuid_utoa (state->fd->inode->gfid), state->type);
                break;
        }


        GF_PROTOCOL_DICT_UNSERIALIZE (state->conn->bound_xl, state->xdata,
                                      (args.xdata.xdata_val),
                                      (args.xdata.xdata_len), ret,
                                      op_errno, out);

        ret = 0;
        resolve_and_resume (frame, server_lk_resume);
out:
        free (args.xdata.xdata_val);

        free (args.flock.lk_owner.lk_owner_val);

        if (op_errno)
                req->rpc_err = GARBAGE_ARGS;

        return ret;
}
