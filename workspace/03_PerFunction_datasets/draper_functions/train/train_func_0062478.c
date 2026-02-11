trace_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, fd_t *fd,
                  inode_t *inode, struct iatt *buf,
                  struct iatt *preparent, struct iatt *postparent)
{
        char  *statstr = NULL;
        char  *preparentstr = NULL;
        char  *postparentstr = NULL;

        if (trace_fop_names[GF_FOP_CREATE].enabled) {
                if (op_ret >= 0) {
                        statstr = trace_stat_to_str (buf);
                        preparentstr = trace_stat_to_str (preparent);
                        postparentstr = trace_stat_to_str (postparent);

                        gf_log (this->name, GF_LOG_INFO,
                                "%"PRId64": gfid=%s (op_ret=%d, fd=%p"
                                "*stbuf {%s}, *preparent {%s}, *postparent = "
                                "{%s})", frame->root->unique,
                                uuid_utoa (inode->gfid), op_ret, fd,
                                statstr, preparentstr, postparentstr);

                        if (statstr)
                                GF_FREE (statstr);
                        if (preparentstr)
                                GF_FREE (preparentstr);
                        if (postparentstr)
                                GF_FREE (postparentstr);


                        fd_ctx_set (fd, this, 0);
                } else {
                        gf_log (this->name, GF_LOG_INFO,
                                "%"PRId64": (op_ret=%d, op_errno=%d)",
                                frame->root->unique, op_ret, op_errno);
                }
        }

        frame->local = NULL;
        STACK_UNWIND_STRICT (create, frame, op_ret, op_errno, fd, inode, buf,
                             preparent, postparent);
        return 0;
}
