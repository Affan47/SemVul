afr_sh_data_unlock (call_frame_t *frame, xlator_t *this,
                    afr_lock_cbk_t lock_cbk)
{
        afr_local_t         *local    = NULL;
        afr_internal_lock_t *int_lock = NULL;
        afr_self_heal_t     *sh       = NULL;

        local    = frame->local;
        int_lock = &local->internal_lock;
        sh       = &local->self_heal;

        GF_ASSERT (sh->data_lock_held);

        sh->data_lock_held = _gf_false;
        int_lock->lock_cbk = lock_cbk;
        afr_unlock (frame, this);

        return 0;
}
