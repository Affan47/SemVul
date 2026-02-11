glusterd_shd_is_running ()
{
        glusterd_conf_t *conf = NULL;

        conf = THIS->private;
        GF_ASSERT (conf);
        GF_ASSERT (conf->shd);

        return conf->shd->running;
}
