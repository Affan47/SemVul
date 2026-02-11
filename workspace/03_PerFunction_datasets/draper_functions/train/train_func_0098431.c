glusterd_nodesvc_unlink_socket_file (char *server)
{
        int             ret = 0;
        char            sockfpath[PATH_MAX] = {0,};
        char            rundir[PATH_MAX] = {0,};
        glusterd_conf_t *priv = THIS->private;

        glusterd_get_nodesvc_rundir (server, priv->workdir,
                                     rundir, sizeof (rundir));

        glusterd_nodesvc_set_socket_filepath (rundir, priv->uuid,
                                              sockfpath, sizeof (sockfpath));

        ret = unlink (sockfpath);
        if (ret && (ENOENT == errno)) {
                ret = 0;
        } else {
                gf_log (THIS->name, GF_LOG_ERROR, "Failed to remove %s"
                        " error: %s", sockfpath, strerror (errno));
        }

        return ret;
}
