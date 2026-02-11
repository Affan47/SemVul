glusterd_store_brickinfopath_set (glusterd_volinfo_t *volinfo,
                              glusterd_brickinfo_t *brickinfo,
                              char *brickpath, size_t len)
{
        char                    brickfname[PATH_MAX] = {0};
        char                    brickdirpath[PATH_MAX] = {0,};
        glusterd_conf_t         *priv = NULL;

        GF_ASSERT (brickpath);
        GF_ASSERT (brickinfo);
        GF_ASSERT (len >= PATH_MAX);

        priv = THIS->private;
        GF_ASSERT (priv);

        GLUSTERD_GET_BRICK_DIR (brickdirpath, volinfo, priv);
        glusterd_store_brickinfofname_set (brickinfo, brickfname,
                                        sizeof (brickfname));
        snprintf (brickpath, len, "%s/%s", brickdirpath, brickfname);
}
