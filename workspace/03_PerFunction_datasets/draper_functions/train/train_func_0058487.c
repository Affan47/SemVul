quiesce_create (call_frame_t *frame, xlator_t *this,
		loc_t *loc, int32_t flags, mode_t mode,
                mode_t umask, fd_t *fd, dict_t *xdata)
{
	quiesce_priv_t *priv = NULL;
        call_stub_t    *stub = NULL;

        priv = this->private;

        if (priv->pass_through) {


                STACK_WIND (frame, default_create_cbk,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->create,
                            loc, (flags & ~O_APPEND), mode, umask, fd, xdata);
                return 0;
        }

        stub = fop_create_stub (frame, default_create_resume,
                                loc, (flags & ~O_APPEND), mode, umask, fd, xdata);
        if (!stub) {
                STACK_UNWIND_STRICT (create, frame, -1, ENOMEM,
                                     NULL, NULL, NULL, NULL, NULL, NULL);
                return 0;
        }

        gf_quiesce_enqueue (this, stub);

        return 0;
}
