ecryptfs_enter_linear_subgraph_tf(struct ecryptfs_ctx *ctx,
				  struct param_node *param_node,
				  struct val_node **mnt_params, void **foo)
{
	struct ecryptfs_subgraph_ctx *subgraph_ctx;
	int rc = 0;

	if ((subgraph_ctx = malloc(sizeof(struct ecryptfs_subgraph_ctx)))
	    == NULL) {
		rc = -ENOMEM;
		goto out;
	}
	memset(subgraph_ctx, 0, sizeof(struct ecryptfs_subgraph_ctx));
	if ((rc = ecryptfs_find_key_mod(&subgraph_ctx->key_mod, ctx,
					param_node->val))) {
		syslog(LOG_ERR, "%s: Cannot find key_mod for param_node with "
		       "val = [%s]\n", __FUNCTION__, param_node->val);
		free(subgraph_ctx);
		goto out;
	}
	(*foo) = (void *)subgraph_ctx;
out:
	return rc;
}
