afr_sh_data_fxattrop_fstat_done (call_frame_t *frame, xlator_t *this)
{
        afr_local_t     *local      = NULL;
        afr_self_heal_t *sh = NULL;
        afr_private_t   *priv = NULL;
        int              nsources = 0;
        int              ret = 0;
        int             *old_sources = NULL;
        int             tstamp_source = 0;
        int             i = 0;

        local = frame->local;
        sh = &local->self_heal;
        priv = this->private;

        gf_log (this->name, GF_LOG_DEBUG, "Pending matrix for: %s",
                lkowner_utoa (&frame->root->lk_owner));
        if (sh->sync_done) {


                old_sources = alloca (priv->child_count*sizeof (*old_sources));
                memcpy (old_sources, sh->sources,
                        priv->child_count * sizeof (*old_sources));
        }

        nsources = afr_build_sources (this, sh->xattr, sh->buf, sh->pending_matrix,
                                      sh->sources, sh->success_children,
                                      AFR_DATA_TRANSACTION, NULL, _gf_true);
        if ((nsources == -1)
            && (priv->favorite_child != -1)
            && (sh->child_errno[priv->favorite_child] == 0)) {

                gf_log (this->name, GF_LOG_DEBUG,
                        "Picking favorite child %s as authentic source to "
                        "resolve conflicting data of %s",
                        priv->children[priv->favorite_child]->name,
                        local->loc.path);

                sh->sources[priv->favorite_child] = 1;

                nsources = afr_sh_source_count (sh->sources,
                                                priv->child_count);
        }

        if (nsources == -1) {
                afr_sh_print_split_brain_log (sh->pending_matrix, this,
                                              local->loc.path);
                afr_set_split_brain (this, sh->inode, DONT_KNOW, SPB);

                afr_sh_data_fail (frame, this);
                return 0;
        }

        afr_set_split_brain (this, sh->inode, DONT_KNOW, NO_SPB);

        ret = afr_sh_inode_set_read_ctx (sh, this);
        if (ret) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "No active sources found.");

                afr_sh_data_fail (frame, this);
                return 0;
        }

        if (sh->sync_done) {


                tstamp_source = sh->source;
                for (i = 0; i < priv->child_count; i++) {
                        if (old_sources[i] && sh->sources[i])
                                tstamp_source = i;
                }
                afr_sh_data_setattr (frame, this, &sh->buf[tstamp_source]);
        } else {
                if (nsources == 0) {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "No self-heal needed for %s",
                                local->loc.path);

                        afr_sh_data_finish (frame, this);
                        return 0;
                }

                if (sh->do_data_self_heal &&
                    afr_data_self_heal_enabled (priv->data_self_heal))
                        afr_sh_data_fix (frame, this);
                else
                        afr_sh_data_finish (frame, this);
        }
        return 0;
}
