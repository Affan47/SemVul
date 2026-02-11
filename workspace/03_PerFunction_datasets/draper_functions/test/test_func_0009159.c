server_submit_reply (call_frame_t *frame, rpcsvc_request_t *req, void *arg,
                     struct iovec *payload, int payloadcount,
                     struct iobref *iobref, xdrproc_t xdrproc)
{
        struct iobuf           *iob        = NULL;
        int                     ret        = -1;
        struct iovec            rsp        = {0,};
        server_state_t         *state      = NULL;
        char                    new_iobref = 0;

        GF_VALIDATE_OR_GOTO ("server", req, ret);

        if (frame) {
                state = CALL_STATE (frame);
                frame->local = NULL;
        }

        if (!iobref) {
                iobref = iobref_new ();
                if (!iobref) {
                        goto ret;
                }

                new_iobref = 1;
        }

        iob = gfs_serialize_reply (req, arg, &rsp, xdrproc);
        if (!iob) {
                gf_log ("", GF_LOG_ERROR, "Failed to serialize reply");
                goto ret;
        }

        iobref_add (iobref, iob);


        ret = rpcsvc_submit_generic (req, &rsp, 1, payload, payloadcount,
                                     iobref);


        iobuf_unref (iob);
        if (ret == -1) {
                gf_log_callingfn ("", GF_LOG_ERROR, "Reply submission failed");
                goto ret;
        }

        ret = 0;
ret:
        if (state) {
                free_state (state);
        }

        if (frame) {
                STACK_DESTROY (frame->root);
        }

        if (new_iobref) {
                iobref_unref (iobref);
        }

        return ret;
}
