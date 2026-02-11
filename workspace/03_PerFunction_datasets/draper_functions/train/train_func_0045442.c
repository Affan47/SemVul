server_lookup (rpcsvc_request_t *req)
{
        call_frame_t        *frame                  = NULL;
        server_connection_t *conn                   = NULL;
        server_state_t      *state                  = NULL;
        dict_t              *xattr_req              = NULL;
        char                *buf                    = NULL;
        gfs3_lookup_req      args                   = {{0,},};
        int                  ret                    = -1;

        GF_VALIDATE_OR_GOTO ("server", req, err);

        conn = req->trans->xl_private;

        args.path          = alloca (req->msg[0].iov_len);
        args.bname         = alloca (req->msg[0].iov_len);
        args.dict.dict_val = alloca (req->msg[0].iov_len);

        if (!xdr_to_generic (req->msg[0], &args, (xdrproc_t)xdr_gfs3_lookup_req)) {

                req->rpc_err = GARBAGE_ARGS;
                goto err;
        }

        frame = get_frame_from_request (req);
        if (!frame) {

                req->rpc_err = GARBAGE_ARGS;
                goto err;
        }
        frame->root->op = GF_FOP_LOOKUP;


        state = CALL_STATE (frame);
        if (!state->conn->bound_xl) {

                req->rpc_err = GARBAGE_ARGS;
                goto out;
        }
        memcpy (state->resolve.gfid, args.gfid, 16);

        state->resolve.type   = RESOLVE_DONTCARE;
        memcpy (state->resolve.pargfid, args.pargfid, 16);
        state->resolve.path   = gf_strdup (args.path);

        if (IS_NOT_ROOT (STRLEN_0 (args.path))) {
                state->resolve.bname = gf_strdup (args.bname);
        }

        if (args.dict.dict_len) {

                xattr_req = dict_new ();

                buf = memdup (args.dict.dict_val, args.dict.dict_len);
                if (buf == NULL) {
                        goto out;
                }

                ret = dict_unserialize (buf, args.dict.dict_len,
                                        &xattr_req);
                if (ret < 0) {
                        gf_log (conn->bound_xl->name, GF_LOG_ERROR,
                                "%"PRId64": %s (%s): failed to "
                                "unserialize req-buffer to dictionary",
                                frame->root->unique, state->resolve.path,
                                uuid_utoa (state->resolve.gfid));
                        goto out;
                }

                state->dict = xattr_req;

                xattr_req->extra_free = buf;

                buf = NULL;
        }

        ret = 0;
        resolve_and_resume (frame, server_lookup_resume);

        return ret;
out:
        if (xattr_req)
                dict_unref (xattr_req);

        if (buf) {
                GF_FREE (buf);
        }

        server_lookup_cbk (frame, NULL, frame->this, -1, EINVAL, NULL, NULL,
                           NULL, NULL);
        ret = 0;
err:
        return ret;
}
