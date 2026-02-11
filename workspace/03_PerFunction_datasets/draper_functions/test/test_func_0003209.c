libcdata_tree_node_set_nodes(
     libcdata_tree_node_t *node,
     libcdata_tree_node_t *parent_node,
     libcdata_tree_node_t *previous_node,
     libcdata_tree_node_t *next_node,
     libcerror_error_t **error )
{
	libcdata_internal_tree_node_t *internal_node = NULL;
	static char *function                        = "libcdata_tree_node_set_nodes";

	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
	internal_node = (libcdata_internal_tree_node_t *) node;

	internal_node->parent_node   = parent_node;
	internal_node->previous_node = previous_node;
	internal_node->next_node     = next_node;

	return( 1 );
}
