rpcsvc_transport_peer_check_allow (dict_t *options, char *volname, char *clstr)
{
        int     ret = RPCSVC_AUTH_DONTCARE;
        char    *srchstr = NULL;
        char    globalrule[] = "rpc-auth.addr.allow";

        if ((!options) || (!clstr))
                return ret;


        if (volname) {
                ret = gf_asprintf (&srchstr, "rpc-auth.addr.%s.allow", volname);
                if (ret == -1) {
                        gf_log (GF_RPCSVC, GF_LOG_ERROR, "asprintf failed");
                        ret = RPCSVC_AUTH_DONTCARE;
                        goto out;
                }
        } else
                srchstr = globalrule;

        ret = rpcsvc_transport_peer_check_search (options, srchstr, clstr);
        if (volname)
                GF_FREE (srchstr);

        if (ret == 0)
                ret = RPCSVC_AUTH_ACCEPT;
        else
                ret = RPCSVC_AUTH_DONTCARE;
out:
        return ret;
}
