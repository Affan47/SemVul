afr_sh_entry_impunge_create (call_frame_t *impunge_frame, xlator_t *this,
                             int child_index)
{
        call_frame_t    *frame             = NULL;
        afr_local_t     *impunge_local     = NULL;
        afr_local_t     *local             = NULL;
        afr_self_heal_t *impunge_sh        = NULL;
        afr_self_heal_t *sh                = NULL;
        afr_private_t   *priv = NULL;
        ia_type_t       type = IA_INVAL;
        int             active_src = 0;
        struct iatt     *buf = NULL;

        AFR_INIT_SH_FRAME_VALS (impunge_frame, impunge_local, impunge_sh,
                                frame, local, sh);
        active_src = impunge_sh->active_source;
        afr_update_loc_gfids (&impunge_local->loc, &impunge_sh->entrybuf,
                              &impunge_sh->parentbuf);

        buf = &impunge_sh->entrybuf;
        type = buf->ia_type;

        switch (type) {
        case IA_IFSOCK:
        case IA_IFREG:
        case IA_IFBLK:
        case IA_IFCHR:
        case IA_IFIFO:
        case IA_IFLNK:
                afr_sh_entry_impunge_check_hardlink (impunge_frame, this,
                                                     child_index, buf);
                break;
        case IA_IFDIR:
                afr_sh_entry_impunge_mkdir (impunge_frame, this,
                                            child_index, buf);
                break;
        default:
                gf_log (this->name, GF_LOG_ERROR,
                        "%s has unknown file type on %s: 0%o",
                        impunge_local->loc.path,
                        priv->children[active_src]->name, type);
                sh->impunge_done (frame, this, -1, EINVAL);
                break;
        }

        return 0;
}
