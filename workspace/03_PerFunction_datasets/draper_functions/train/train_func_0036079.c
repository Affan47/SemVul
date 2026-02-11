afr_proactive_self_heal (xlator_t *this, int idx)
{
        afr_private_t              *priv = NULL;
        afr_self_heald_t           *shd = NULL;
        call_frame_t               *frame = NULL;
        afr_crawl_data_t           *crawl_data = NULL;
        int                        ret = 0;

        priv = this->private;
        shd = &priv->shd;
        if (!shd->enabled)
                goto out;

        if ((idx != AFR_ALL_CHILDREN) &&
            (shd->pos[idx] == AFR_POS_REMOTE))
                goto out;

        frame = create_frame (this, this->ctx->pool);
        if (!frame)
                goto out;

        afr_set_lk_owner (frame, this);
        afr_set_low_priority (frame);
        crawl_data = GF_CALLOC (1, sizeof (*crawl_data),
                                gf_afr_mt_afr_crawl_data_t);
        if (!crawl_data)
                goto out;
        crawl_data->child = idx;
        crawl_data->pid = frame->root->pid;
        gf_log (this->name, GF_LOG_INFO, "starting crawl for %d", idx);
        ret = synctask_new (this->ctx->env, afr_crawl,
                            afr_crawl_done, frame, crawl_data);
        if (ret)
                gf_log (this->name, GF_LOG_ERROR, "Could not create the "
                        "task for %d ret %d", idx, ret);
out:
        return;
}
