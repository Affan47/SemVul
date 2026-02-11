quiesce_open (call_frame_t *frame,
	      xlator_t *this,
	      loc_t *loc,
	      int32_t flags, fd_t *fd,
              dict_t *xdata)
{
	quiesce_priv_t *priv = NULL;
        call_stub_t    *stub = NULL;
        quiesce_local_t *local = NULL;

        priv = this->private;

        if (priv && priv->pass_through) {
                local = mem_get0 (priv->local_pool);
                loc_dup (loc, &local->loc);
                local->fd = fd_ref (fd);


                local->flag = (flags & ~O_APPEND);
                frame->local = local;

                STACK_WIND (frame,
                            quiesce_open_cbk,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->open,
                            loc, (flags & ~O_APPEND), fd, xdata);
                return 0;
        }

        stub = fop_open_stub (frame, default_open_resume, loc,
                              (flags & ~O_APPEND), fd, xdata);
        if (!stub) {
                STACK_UNWIND_STRICT (open, frame, -1, ENOMEM, NULL, NULL);
                return 0;
        }

        gf_quiesce_enqueue (this, stub);

        return 0;
}
