afr_sh_find_fresh_parents (call_frame_t *frame, xlator_t *this,
                           int32_t op_ret, int32_t op_errno)
{
        afr_self_heal_t *sh  = NULL;
        afr_private_t   *priv = NULL;
        afr_local_t     *local = NULL;
        int             enoent_count = 0;
        int             nsources = 0;
        int             source  = -1;
        int32_t         subvol_status = 0;

        local = frame->local;
        sh = &local->self_heal;
        priv = this->private;

        if (op_ret < 0)
                goto out;
        enoent_count = afr_errno_count (NULL, sh->child_errno,
                                        priv->child_count, ENOENT);
        if (enoent_count > 0) {
                gf_log (this->name, GF_LOG_INFO, "Parent dir missing for %s,"
                        " in missing entry self-heal, aborting missing-entry "
                        "self-heal",
                        local->loc.path);
                afr_sh_missing_entries_finish (frame, this);
                return;
        }

        nsources = afr_build_sources (this, sh->xattr, sh->buf,
                                      sh->pending_matrix, sh->sources,
                                      sh->success_children,
                                      AFR_ENTRY_TRANSACTION, &subvol_status,
                                      _gf_true);
        if ((subvol_status & ALL_FOOLS) ||
            (subvol_status & SPLIT_BRAIN)) {
                gf_log (this->name, GF_LOG_INFO, "%s: Performing conservative "
                        "merge", sh->parent_loc.path);
                afr_mark_success_children_sources (sh->sources,
                                                   sh->success_children,
                                                   priv->child_count);
        } else if (nsources < 0) {
                gf_log (this->name, GF_LOG_ERROR, "No sources for dir "
                        "of %s, in missing entry self-heal, aborting "
                        "self-heal", local->loc.path);
                op_errno = EIO;
                goto out;
        }

        source = afr_sh_select_source (sh->sources, priv->child_count);
        if (source == -1) {
                GF_ASSERT (0);
                gf_log (this->name, GF_LOG_DEBUG, "No active sources found.");
                op_errno = EIO;
                goto out;
        }
        afr_get_fresh_children (sh->success_children, sh->sources,
                                sh->fresh_parent_dirs, priv->child_count);
        afr_sh_common_lookup (frame, this, &local->loc,
                              afr_sh_children_lookup_done, NULL, 0,
                              NULL);
        return;

out:
        afr_sh_set_error (sh, op_errno);
        sh->op_failed = 1;
        afr_sh_missing_entries_finish (frame, this);
        return;
}
