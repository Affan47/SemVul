glusterd_rebalance_rpc_create (glusterd_volinfo_t *volinfo,
                               glusterd_conf_t *priv, int cmd)
{
        dict_t                  *options = NULL;
        char                     sockfile[PATH_MAX] = {0,};
        int                      ret = -1;
        glusterd_defrag_info_t  *defrag =  NULL;

        if (!volinfo->defrag)
                volinfo->defrag = GF_CALLOC (1, sizeof (glusterd_defrag_info_t),
                                             gf_gld_mt_defrag_info);
        if (!volinfo->defrag)
                goto out;

        defrag = volinfo->defrag;

        defrag->cmd = cmd;

        LOCK_INIT (&defrag->lock);

        GLUSTERD_GET_DEFRAG_SOCK_FILE (sockfile, volinfo, priv);
        ret = rpc_clnt_transport_unix_options_build (&options, sockfile);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "Unix options build failed");
                goto out;
        }

        ret = glusterd_rpc_create (&defrag->rpc, options,
                                   glusterd_defrag_notify, volinfo);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "RPC create failed");
                goto out;
        }
        ret = 0;
out:
        return ret;
}
