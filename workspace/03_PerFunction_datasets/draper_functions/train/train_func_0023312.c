libcdata_tree_node_replace_node(
     libcdata_tree_node_t *node,
     libcdata_tree_node_t *replacement_node,
     libcerror_error_t **error )
{
	libcdata_internal_tree_node_t *internal_node             = NULL;
	libcdata_internal_tree_node_t *internal_replacement_node = NULL;
	libcdata_tree_node_t *first_sub_node                     = NULL;
	libcdata_tree_node_t *last_sub_node                      = NULL;
	libcdata_tree_node_t *sub_node                           = NULL;
	intptr_t *value                                          = NULL;
	static char *function                                    = "libcdata_tree_node_replace_node";
	int number_of_sub_nodes                                  = 0;
	int sub_node_index                                       = 0;

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

	if( replacement_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid replacement node.",
		 function );

		return( -1 );
	}
	internal_replacement_node = (libcdata_internal_tree_node_t *) replacement_node;

	if( replacement_node == node )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: cannot replace node with itself.",
		 function );

		return( -1 );
	}
	if( ( internal_replacement_node->parent_node != NULL )
	 || ( internal_replacement_node->previous_node != NULL )
	 || ( internal_replacement_node->next_node != NULL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid replacement node - node is already part of a tree.",
		 function );

		return( -1 );
	}
	value               = internal_node->value;
	first_sub_node      = internal_node->first_sub_node;
	last_sub_node       = internal_node->last_sub_node;
	number_of_sub_nodes = internal_node->number_of_sub_nodes;

	internal_node->value               = internal_replacement_node->value;
	internal_node->first_sub_node      = internal_replacement_node->first_sub_node;
	internal_node->last_sub_node       = internal_replacement_node->last_sub_node;
	internal_node->number_of_sub_nodes = internal_replacement_node->number_of_sub_nodes;

	internal_replacement_node->value               = value;
	internal_replacement_node->first_sub_node      = first_sub_node;
	internal_replacement_node->last_sub_node       = last_sub_node;
	internal_replacement_node->number_of_sub_nodes = number_of_sub_nodes;

	sub_node = internal_node->first_sub_node;

	for( sub_node_index = 0;
	     sub_node_index < internal_node->number_of_sub_nodes;
	     sub_node_index++ )
	{
		if( libcdata_tree_node_set_parent_node(
		     sub_node,
		     node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set parent node value of sub node: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
		if( libcdata_tree_node_get_next_node(
		     sub_node,
		     &sub_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node of sub node: %d.",
			 function,
			 sub_node_index );

			return( -1 );
		}
	}
	return( 1 );
}
