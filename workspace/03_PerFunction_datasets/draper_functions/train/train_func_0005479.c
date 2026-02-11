cluster_collect_summaries_recursive(struct cluster *c, struct list *accum)
{
	if( !c->right && !c->left)
		list_push_head(accum, c->centroid);

	if( c->left )
		cluster_collect_summaries_recursive(c->left, accum);

	if( c->right )
		cluster_collect_summaries_recursive(c->right, accum);
}
