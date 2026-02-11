pump_set_resume_path (xlator_t *this, const char *path)
{
        int ret = 0;

        afr_private_t *priv = NULL;
        pump_private_t *pump_priv = NULL;

        priv = this->private;
        pump_priv = priv->pump_private;

        GF_ASSERT (pump_priv);

        LOCK (&pump_priv->resume_path_lock);
        {
                strncpy (pump_priv->resume_path, path, strlen (path) + 1);
        }
        UNLOCK (&pump_priv->resume_path_lock);

        return ret;
}
