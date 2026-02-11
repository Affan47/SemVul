afr_sh_post_nb_entrylk_conflicting_sh_cbk (call_frame_t *frame, xlator_t *this)
{
        afr_internal_lock_t *int_lock = NULL;
        afr_local_t         *local    = NULL;
        afr_self_heal_t     *sh       = NULL;

        local    = frame->local;
        int_lock = &local->internal_lock;
        sh       = &local->self_heal;

        if (int_lock->lock_op_ret < 0) {
                gf_log (this->name, GF_LOG_INFO,
                        "Non blocking entrylks failed.");
                sh->op_failed = -1;
                afr_sh_missing_entries_done (frame, this);
        } else {

                gf_log (this->name, GF_LOG_DEBUG,
                        "Non blocking entrylks done. Proceeding to FOP");
                afr_sh_common_lookup (frame, this, &sh->parent_loc,
                                      afr_sh_find_fresh_parents,
                                      NULL, AFR_LOOKUP_FAIL_CONFLICTS,
                                      NULL);
        }

        return 0;
}
