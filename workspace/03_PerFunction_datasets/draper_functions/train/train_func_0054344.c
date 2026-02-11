glusterd_nodesvc_stop (char *server, int sig)
{
        char                    pidfile[PATH_MAX] = {0,};
        glusterd_conf_t         *priv = THIS->private;
        int                     ret = 0;

        if (!glusterd_is_nodesvc_running (server))
                goto out;
        glusterd_get_nodesvc_pidfile (server, priv->workdir,
                                            pidfile, sizeof (pidfile));
        ret = glusterd_service_stop (server, pidfile, sig, _gf_true);
out:
        return ret;
}
