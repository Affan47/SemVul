afr_sh_entry_expunge_parent_setattr_cbk (call_frame_t *expunge_frame,
                                         void *cookie, xlator_t *this,
                                         int32_t op_ret, int32_t op_errno,
                                         struct iatt *preop, struct iatt *postop)
{
        afr_private_t   *priv          = NULL;
        afr_local_t     *expunge_local = NULL;
        afr_self_heal_t *expunge_sh    = NULL;
        call_frame_t    *frame         = NULL;
        int              active_src    = (long) cookie;
        afr_self_heal_t *sh            = NULL;
        afr_local_t     *local         = NULL;

        priv          = this->private;
        expunge_local = expunge_frame->local;
        expunge_sh    = &expunge_local->self_heal;
        frame         = expunge_sh->sh_frame;
        local         = frame->local;
        sh            = &local->self_heal;

        if (op_ret != 0) {
                gf_log (this->name, GF_LOG_ERROR,
                        "setattr on parent directory of %s on subvolume %s failed: %s",
                        expunge_local->loc.path,
                        priv->children[active_src]->name, strerror (op_errno));
        }

        AFR_STACK_DESTROY (expunge_frame);
        sh->expunge_done (frame, this, active_src, op_ret, op_errno);

        return 0;
}
