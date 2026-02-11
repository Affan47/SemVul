tree_done_node_detached(struct tree *t, struct tree_node *n)
{
	if (n->u.playouts < 1000) {
		if (!tree_done_node(t, n))
			free(t);
		return;
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_t thread;
	struct subtree_ctx *ctx = malloc2(sizeof(struct subtree_ctx));
	ctx->t = t;
	ctx->n = n;
	pthread_create(&thread, &attr, tree_done_node_worker, ctx);
	pthread_attr_destroy(&attr);
}
