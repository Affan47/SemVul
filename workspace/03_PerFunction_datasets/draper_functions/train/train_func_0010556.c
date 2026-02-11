pump_getxattr (call_frame_t *frame, xlator_t *this,
	      loc_t *loc, const char *name, dict_t *xdata)
{
	afr_private_t *   priv       = NULL;
	xlator_t **       children   = NULL;
	int               call_child = 0;
	afr_local_t       *local     = NULL;
	int32_t           ret     = -1;
	int32_t           op_errno   = 0;
        uint64_t          read_child = 0;


	VALIDATE_OR_GOTO (frame, out);
	VALIDATE_OR_GOTO (this, out);
	VALIDATE_OR_GOTO (this->private, out);

	priv     = this->private;
	VALIDATE_OR_GOTO (priv->children, out);

	children = priv->children;
        if (!priv->use_afr_in_pump) {
                STACK_WIND (frame, default_getxattr_cbk,
                            FIRST_CHILD (this),
                            (FIRST_CHILD (this))->fops->getxattr,
                            loc, name, xdata);
                return 0;
        }


	AFR_LOCAL_ALLOC_OR_GOTO (frame->local, out);
	local = frame->local;

        ret = afr_local_init (local, priv, &op_errno);
        if (ret < 0)
                goto out;

        if (name) {
                if (!strncmp (name, AFR_XATTR_PREFIX,
                              strlen (AFR_XATTR_PREFIX))) {

                        op_errno = ENODATA;
                        goto out;
                }

                if (!strcmp (name, RB_PUMP_CMD_STATUS)) {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "Hit pump command - status");
                        pump_execute_status (frame, this);
                        ret = 0;
                        goto out;
                }
        }

        local->fresh_children = GF_CALLOC (priv->child_count,
                                          sizeof (*local->fresh_children),
                                          gf_afr_mt_int32_t);
        if (!local->fresh_children) {
                ret = -1;
                op_errno = ENOMEM;
                goto out;
        }

        read_child = afr_inode_get_read_ctx (this, loc->inode, local->fresh_children);
        ret = afr_get_call_child (this, local->child_up, read_child,
                                     local->fresh_children,
                                     &call_child,
                                     &local->cont.getxattr.last_index);
        if (ret < 0) {
                op_errno = -ret;
                goto out;
        }
	loc_copy (&local->loc, loc);
	if (name)
	  local->cont.getxattr.name       = gf_strdup (name);

	STACK_WIND_COOKIE (frame, pump_getxattr_cbk,
			   (void *) (long) call_child,
			   children[call_child], children[call_child]->fops->getxattr,
			   loc, name, xdata);

	ret = 0;
out:
	if (ret < 0)
		AFR_STACK_UNWIND (getxattr, frame, -1, op_errno, NULL, NULL);
	return 0;
}
