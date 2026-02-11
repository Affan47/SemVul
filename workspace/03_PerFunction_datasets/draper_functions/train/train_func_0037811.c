afr_sh_purge_stale_entries_done (call_frame_t *frame, xlator_t *this)
{
        afr_local_t         *local    = NULL;
        afr_self_heal_t     *sh       = NULL;
        afr_private_t       *priv     = NULL;

        local    = frame->local;
        sh       = &local->self_heal;
        priv     = this->private;

        if (sh->op_failed) {
                afr_sh_missing_entries_finish (frame, this);
        } else {
                if (afr_gfid_missing_count (this->name, sh->fresh_children,
                                            sh->buf, priv->child_count,
                                            local->loc.path)) {
                        afr_sh_common_lookup (frame, this, &local->loc,
                                              afr_sh_missing_entries_lookup_done,
                                              sh->sh_gfid_req,
                                              AFR_LOOKUP_FAIL_CONFLICTS|
                                              AFR_LOOKUP_FAIL_MISSING_GFIDS,
                                              NULL);
                } else {


                        afr_sh_remove_stale_lookup_info (sh,
                                                         sh->success_children,
                                                         sh->fresh_children,
                                                         priv->child_count);
                        afr_children_copy (sh->success_children,
                                           sh->fresh_children,
                                           priv->child_count);
                        afr_sh_missing_entries_lookup_done (frame, this, 0, 0);
                }
        }
        return 0;
}
