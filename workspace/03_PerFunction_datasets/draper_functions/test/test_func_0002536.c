fuse_truncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                   struct iatt *postbuf, dict_t *xdata)
{
        fuse_state_t     *state;
        fuse_in_header_t *finh;
        fuse_private_t   *priv = NULL;
        struct fuse_attr_out fao;

        priv  = this->private;
        state = frame->root->state;
        finh  = state->finh;

        if (op_ret == 0) {
                gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                        "%"PRIu64": %s() %s => %"PRId64, frame->root->unique,
                        gf_fop_list[frame->root->op],
                        state->loc.path ? state->loc.path : "ERR",
                        prebuf->ia_ino);

                postbuf->ia_blksize = this->ctx->page_size;
                gf_fuse_stat2attr (postbuf, &fao.attr);

                fao.attr_valid = calc_timeout_sec (priv->attribute_timeout);
                fao.attr_valid_nsec =
                  calc_timeout_nsec (priv->attribute_timeout);

#if FUSE_KERNEL_MINOR_VERSION >= 9
                priv->proto_minor >= 9 ?
                send_fuse_obj (this, finh, &fao) :
                send_fuse_data (this, finh, &fao,
                                FUSE_COMPAT_ATTR_OUT_SIZE);
#else
                send_fuse_obj (this, finh, &fao);
#endif
        } else {
                gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                        "%"PRIu64": %s() %s => -1 (%s)", frame->root->unique,
                        gf_fop_list[frame->root->op],
                        state->loc.path ? state->loc.path : "ERR",
                        strerror (op_errno));

                send_fuse_err (this, finh, op_errno);
        }

        free_fuse_state (state);
        STACK_DESTROY (frame->root);

        return 0;
}
