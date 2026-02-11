sh_loop_write_cbk (call_frame_t *loop_frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *buf,
                   struct iatt *postbuf, dict_t *xdata)
{
        afr_private_t *             priv        = NULL;
        afr_local_t *               loop_local    = NULL;
        afr_self_heal_t *           loop_sh       = NULL;
        call_frame_t               *sh_frame    = NULL;
        afr_local_t *               sh_local    = NULL;
        afr_self_heal_t            *sh          = NULL;
        int                         call_count  = 0;
        int                         child_index = 0;

        priv     = this->private;
        loop_local = loop_frame->local;
        loop_sh    = &loop_local->self_heal;

        sh_frame = loop_sh->sh_frame;
        sh_local = sh_frame->local;
        sh       = &sh_local->self_heal;

        child_index =  (long) cookie;

        gf_log (this->name, GF_LOG_TRACE,
                "wrote %d bytes of data from %s to child %d, offset %"PRId64"",
                op_ret, sh_local->loc.path, child_index, loop_sh->offset);

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_ERROR,
                        "write to %s failed on subvolume %s (%s)",
                        sh_local->loc.path,
                        priv->children[child_index]->name,
                        strerror (op_errno));

                sh->op_failed = 1;
                afr_sh_set_error (loop_sh, op_errno);
        } else if (op_ret < loop_local->cont.writev.vector->iov_len) {
		gf_log(this->name, GF_LOG_ERROR,
		       "incomplete write to %s on subvolume %s "
		       "(expected %lu, returned %d)", sh_local->loc.path,
		       priv->children[child_index]->name,
		       loop_local->cont.writev.vector->iov_len, op_ret);
		sh->op_failed = 1;
	}

        call_count = afr_frame_return (loop_frame);

        if (call_count == 0) {
		iobref_unref(loop_local->cont.writev.iobref);

                sh_loop_return (sh_frame, this, loop_frame,
                                loop_sh->op_ret, loop_sh->op_errno);
        }

        return 0;
}
