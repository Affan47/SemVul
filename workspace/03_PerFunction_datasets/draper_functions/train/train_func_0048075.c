pump_execute_commit (call_frame_t *frame, xlator_t *this)
{
        afr_private_t  *priv       = NULL;
        pump_private_t *pump_priv  = NULL;
        afr_local_t    *local      = NULL;
        call_frame_t   *sync_frame = NULL;
        int             ret        = 0;

        priv      = this->private;
        pump_priv = priv->pump_private;
        local     = frame->local;

        local->op_ret = 0;
        if (pump_priv->pump_finished) {
                pump_change_state (this, PUMP_STATE_COMMIT);
                sync_frame = create_frame (this, this->ctx->pool);
                ret = synctask_new (pump_priv->env, pump_cleanup_helper,
                                    pump_cleanup_done, sync_frame, frame);
                if (ret) {
                        gf_log (this->name, GF_LOG_DEBUG, "Couldn't create "
                                "synctask for cleaning up xattrs.");
                }

        } else {
                gf_log (this->name, GF_LOG_ERROR, "Commit can't proceed. "
                        "Migration in progress");
                local->op_ret = -1;
                local->op_errno = EINPROGRESS;
                pump_command_reply (frame, this);
        }

        return 0;
}
