pump_create (call_frame_t *frame, xlator_t *this,
             loc_t *loc, int32_t flags, mode_t mode,
             fd_t *fd, dict_t *params)
{
        afr_private_t *priv  = NULL;
	priv = this->private;
        if (!priv->use_afr_in_pump) {
                STACK_WIND (frame, default_create_cbk,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->create,
                            loc, flags, mode, fd, params);
                return 0;
        }
        afr_create (frame, this, loc, flags, mode, fd, params);
        return 0;

}
