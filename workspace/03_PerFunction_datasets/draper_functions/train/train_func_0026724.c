fini (xlator_t *this)
{
        index_priv_t *priv = NULL;

        priv = this->private;
        if (!priv)
                goto out;
        this->private = NULL;
        LOCK_DESTROY (&priv->lock);
        pthread_cond_destroy (&priv->cond);
        pthread_mutex_destroy (&priv->mutex);
        GF_FREE (priv);
out:
        return;
}
