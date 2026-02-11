nfs3svc_mkdir (rpcsvc_request_t *req)
{
        char                    name[NFS_PATH_MAX];
        struct nfs3_fh          dirfh = {{0}, };
        mkdir3args              args;
        int                     ret = RPCSVC_ACTOR_ERROR;

        if (!req)
                return ret;
        nfs3_prep_mkdir3args (&args, &dirfh, name);
        if (xdr_to_mkdir3args (req->msg[0], &args) <= 0) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Error decoding args");
                rpcsvc_request_seterr (req, GARBAGE_ARGS);
                goto rpcerr;
        }

        ret = nfs3_mkdir (req, &dirfh, name, &args.attributes);
        if ((ret < 0) && (ret != RPCSVC_ACTOR_IGNORE)) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "MKDIR procedure failed");
                rpcsvc_request_seterr (req, SYSTEM_ERR);
                ret = RPCSVC_ACTOR_ERROR;
        }

rpcerr:
        return ret;
}
