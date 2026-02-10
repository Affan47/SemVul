pump_execute_abort (call_frame_t *frame, xlator_t *this)
{
        afr_private_t  *priv       = NULL;
        pump_private_t *pump_priv  = NULL;
        afr_local_t    *local      = NULL;
        call_frame_t   *sync_frame = NULL;
        int             ret        = 0;

        priv      = this->private;
        pump_priv = priv->pump_private;
        local     = frame->local;

        pump_change_state (this, PUMP_STATE_ABORT);

        LOCK (&pump_priv->resume_path_lock);
        {
                pump_priv->number_files_pumped = 0;
                pump_priv->current_file[0] = '\0';
        }
        UNLOCK (&pump_priv->resume_path_lock);

        local->op_ret = 0;
        if (pump_priv->pump_finished) {
                sync_frame = create_frame (this, this->ctx->pool);
                ret = synctask_new (pump_priv->env, pump_cleanup_helper,
                                    pump_cleanup_done, sync_frame, frame);
                if (ret) {
                        gf_log (this->name, GF_LOG_DEBUG, "Couldn't create "
                                "synctask for cleaning up xattrs.");
                }

        } else {
                pump_priv->cleaner = fop_setxattr_cbk_stub (frame,
                                                            pump_xattr_cleaner,
                                                            0, 0, NULL);
        }

        return 0;
}
