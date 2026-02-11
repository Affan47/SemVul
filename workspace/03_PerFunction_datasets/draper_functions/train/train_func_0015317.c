afr_poll_self_heal (void *data)
{
        afr_private_t    *priv = NULL;
        afr_self_heald_t *shd = NULL;
        struct timeval   timeout = {0};
        xlator_t         *this = NULL;
        long             child = (long)data;
        gf_timer_t       *old_timer = NULL;
        gf_timer_t       *new_timer = NULL;

        this = THIS;
        priv = this->private;
        shd = &priv->shd;

        _do_self_heal_on_subvol (this, child, INDEX);
        timeout.tv_sec = AFR_POLL_TIMEOUT;
        timeout.tv_usec = 0;

        LOCK (&priv->lock);
        {
                old_timer = shd->timer[child];
                shd->timer[child] = gf_timer_call_after (this->ctx, timeout,
                                                         afr_poll_self_heal,
                                                         data);
                new_timer = shd->timer[child];
        }
        UNLOCK (&priv->lock);

        if (old_timer)
                gf_timer_call_cancel (this->ctx, old_timer);
        if (!new_timer) {
                gf_log (this->name, GF_LOG_WARNING,
                        "Could not create self-heal polling timer for %s",
                        priv->children[child]->name);
        }
        return;
}
