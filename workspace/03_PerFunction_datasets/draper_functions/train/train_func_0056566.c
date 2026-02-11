server_create (rpcsvc_request_t *req)
{
        server_state_t      *state                  = NULL;
        call_frame_t        *frame                  = NULL;
        dict_t              *params                 = NULL;
        char                *buf                    = NULL;
        gfs3_create_req      args                   = {{0,},};
        int                  ret                    = -1;

        if (!req)
                return ret;

        args.path  = alloca (req->msg[0].iov_len);
        args.bname = alloca (req->msg[0].iov_len);

        if (!xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_create_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        frame->root->op = GF_FOP_CREATE;

        state = CALL_STATE (frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        if (args.dict.dict_len) {

                params = dict_new ();

                buf = memdup (args.dict.dict_val, args.dict.dict_len);
                if (buf == NULL) {
                        goto out;
                }

                ret = dict_unserialize (buf, args.dict.dict_len,
                                        &params);
                if (ret < 0) {
                        gf_log (state->conn->bound_xl->name, GF_LOG_ERROR,
                                "%"PRId64": %s (%s): failed to "
                                "unserialize req-buffer to dictionary",
                                frame->root->unique, state->resolve.path,
                                uuid_utoa (state->resolve.gfid));
                        goto out;
                }

                state->params = params;

                params->extra_free = buf;

                buf = NULL;
        }

        state->resolve.path   = gf_strdup (args.path);
        state->resolve.bname  = gf_strdup (args.bname);
        state->mode           = args.mode;
        state->flags          = gf_flags_to_flags (args.flags);
        memcpy (state->resolve.pargfid, args.pargfid, 16);

        if (state->flags & O_EXCL) {
                state->resolve.type = RESOLVE_NOT;
        } else {
                state->resolve.type = RESOLVE_DONTCARE;
        }

        ret = 0;
        resolve_and_resume (frame, server_create_resume);


        if (args.dict.dict_val != NULL) {
                free (args.dict.dict_val);
        }

        return ret;
out:
        if (params)
                dict_unref (params);

        if (buf) {
                GF_FREE (buf);
        }


        if (args.dict.dict_val != NULL) {
                free (args.dict.dict_val);
        }

        return ret;
}
