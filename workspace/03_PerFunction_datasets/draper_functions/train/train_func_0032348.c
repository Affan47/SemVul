afr_sh_entry_expunge_remove (call_frame_t *expunge_frame, xlator_t *this,
                             int active_src, struct iatt *buf)
{
        afr_private_t   *priv = NULL;
        afr_local_t     *expunge_local = NULL;
        afr_self_heal_t *expunge_sh = NULL;
        call_frame_t    *frame = NULL;
        int              type = 0;
        afr_self_heal_t *sh            = NULL;
        afr_local_t     *local         = NULL;

        priv = this->private;
        expunge_local = expunge_frame->local;
        expunge_sh = &expunge_local->self_heal;
        frame = expunge_sh->sh_frame;
        local         = frame->local;
        sh            = &local->self_heal;

        type = buf->ia_type;

        switch (type) {
        case IA_IFSOCK:
        case IA_IFREG:
        case IA_IFBLK:
        case IA_IFCHR:
        case IA_IFIFO:
        case IA_IFLNK:
                afr_sh_entry_expunge_unlink (expunge_frame, this, active_src);
                break;
        case IA_IFDIR:
                afr_sh_entry_expunge_rmdir (expunge_frame, this, active_src);
                break;
        default:
                gf_log (this->name, GF_LOG_ERROR,
                        "%s has unknown file type on %s: 0%o",
                        expunge_local->loc.path,
                        priv->children[active_src]->name, type);
                goto out;
                break;
        }

        return 0;
out:
        AFR_STACK_DESTROY (expunge_frame);
        sh->expunge_done (frame, this, active_src, -1, EINVAL);

        return 0;
}
