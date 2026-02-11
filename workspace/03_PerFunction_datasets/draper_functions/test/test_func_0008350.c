rpcsvc_auth_unix_auxgids (rpcsvc_request_t *req, int *arrlen)
{
        if ((!req) || (!arrlen))
                return NULL;


        switch (req->cred.flavour) {
        case AUTH_UNIX:
        case AUTH_GLUSTERFS:
        case AUTH_GLUSTERFS_v2:
                break;
        default:
                gf_log ("rpc", GF_LOG_DEBUG, "auth type not unix or glusterfs");
                return NULL;
        }

        *arrlen = req->auxgidcount;
        if (*arrlen == 0)
                return NULL;

        return &req->auxgids[0];
}
