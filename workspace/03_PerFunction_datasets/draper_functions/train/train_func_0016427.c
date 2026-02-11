nfs3svc_submit_vector_reply (rpcsvc_request_t *req, void *arg,
                             nfs3_serializer sfunc, struct iovec *payload,
                             int vcount, struct iobref *iobref)
{
        struct iovec            outmsg = {0, };
        struct iobuf            *iob = NULL;
        int                     ret = -1;
        int                     new_iobref = 0;

        if (!req)
                return -1;

        iob = nfs3_serialize_reply (req, arg, sfunc, &outmsg);
        if (!iob) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Failed to serialize reply");
                goto ret;
        }
        if (iobref == NULL) {
                iobref = iobref_new ();
                if (!iobref) {
                        gf_log (GF_NFS3, GF_LOG_ERROR, "failed on iobref_new");
                        goto ret;
                }
                new_iobref = 1;
        }

        iobref_add (iobref, iob);


        ret = rpcsvc_submit_message (req, &outmsg, 1, payload, vcount, iobref);


        iobuf_unref (iob);
        if (new_iobref)
                iobref_unref (iobref);

        if (ret == -1) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Reply submission failed");
                goto ret;
        }

        ret = 0;
ret:
        return ret;
}
