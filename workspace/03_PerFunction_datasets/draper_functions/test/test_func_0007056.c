stripe_mknod_first_ifreg_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                        int32_t op_ret, int32_t op_errno, inode_t *inode,
                        struct iatt *buf, struct iatt *preparent,
                        struct iatt *postparent, dict_t *xdata)
{
        stripe_local_t   *local = NULL;
        stripe_private_t *priv = NULL;
        call_frame_t     *prev = NULL;
        xlator_list_t    *trav = NULL;
        int               i    = 1;
        dict_t           *dict           = NULL;
        int               ret            = 0;
        int               need_unref     = 0;

        if (!this || !frame || !frame->local || !cookie) {
                gf_log ("stripe", GF_LOG_DEBUG, "possible NULL deref");
                goto out;
        }

        prev  = cookie;
        priv  = this->private;
        local = frame->local;
        trav = this->children;

        local->call_count--;

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_DEBUG, "%s returned error %s",
                        prev->this->name, strerror (op_errno));
                local->failed = 1;
                local->op_errno = op_errno;
                goto out;
        }

        local->op_ret = op_ret;

        local->stbuf      = *buf;
        local->preparent  = *preparent;
        local->postparent = *postparent;

        if (uuid_is_null (local->ia_gfid))
                uuid_copy (local->ia_gfid, buf->ia_gfid);
        local->preparent.ia_blocks  = local->preparent_blocks;
        local->preparent.ia_size    = local->preparent_size;
        local->postparent.ia_blocks = local->postparent_blocks;
        local->postparent.ia_size   = local->postparent_size;
        local->stbuf.ia_size        = local->stbuf_size;
        local->stbuf.ia_blocks      = local->stbuf_blocks;

        trav = trav->next;
        while (trav) {
                if (priv->xattr_supported) {
                        dict = dict_new ();
                        if (!dict) {
                                gf_log (this->name, GF_LOG_ERROR,
                                        "failed to allocate dict %s", local->loc.path);
                        }
                        need_unref = 1;

                        dict_copy (local->xattr, dict);

                        ret = stripe_xattr_request_build (this, dict,
                                                          local->stripe_size,
                                                          priv->child_count, i,
							  priv->coalesce);
                        if (ret)
                                gf_log (this->name, GF_LOG_ERROR,
                                        "Failed to build xattr request");

                } else {
                        dict = local->xattr;
                }

                STACK_WIND (frame, stripe_mknod_ifreg_cbk,
                            trav->xlator, trav->xlator->fops->mknod,
                            &local->loc, local->mode, local->rdev, 0, dict);
                trav = trav->next;
                i++;

                if (dict && need_unref)
                        dict_unref (dict);
        }

        return 0;

out:

       STRIPE_STACK_UNWIND (mknod, frame, op_ret, op_errno, NULL, NULL, NULL, NULL, NULL);
       return 0;
}
