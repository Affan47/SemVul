eval_param_tree(struct ecryptfs_ctx *ctx, struct param_node *node,
		    struct ecryptfs_name_val_pair *nvp_head,
		    struct val_node **mnt_params)
{
	void *foo = NULL;
	int rc;

	get_verbosity(nvp_head, &(ctx->verbosity));
	do {
		if (ecryptfs_verbosity) {
			int i;

			syslog(LOG_INFO, "%s: Calling alloc_and_get_val() on "
			       "node = [%p]; node->mnt_opt_names[0] = [%s]\n",
			       __FUNCTION__, node, node->mnt_opt_names[0]);
			for (i = 0; i < node->num_transitions; i++) {
				syslog(LOG_INFO,
				       "%s:  node->tl[%d].val = [%s]\n",
				       __FUNCTION__, i, node->tl[i].val);
			}
		}
		if ((rc = alloc_and_get_val(ctx, node, nvp_head)))
			return rc;
	} while (!(rc = do_transition(ctx, &node, node, nvp_head,
				      mnt_params, &foo)));
	return rc;
}
