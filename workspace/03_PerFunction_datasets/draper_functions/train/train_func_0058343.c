quiesce_readdir (call_frame_t *frame,
		 xlator_t *this,
		 fd_t *fd,
		 size_t size,
		 off_t off)
{
	quiesce_priv_t *priv = NULL;
        call_stub_t    *stub = NULL;
        quiesce_local_t *local = NULL;

        priv = this->private;

        if (priv && priv->pass_through) {
                local = mem_get0 (priv->local_pool);
                local->fd = fd_ref (fd);
                local->size = size;
                local->offset = off;
                frame->local = local;

                STACK_WIND (frame,
                            quiesce_readdir_cbk,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->readdir,
                            fd, size, off);
	        return 0;
        }

        stub = fop_readdir_stub (frame, default_readdir_resume, fd, size, off);
        if (!stub) {
                STACK_UNWIND_STRICT (readdir, frame, -1, ENOMEM, NULL);
                return 0;
        }

        gf_quiesce_enqueue (this, stub);

        return 0;
}
