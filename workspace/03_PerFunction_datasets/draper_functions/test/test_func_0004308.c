avl_prefixapply(
    Avlnode	*root,
    caddr_t	data,
    IFP		fmatch,
    caddr_t	marg,
    IFP		fcmp,
    caddr_t	carg,
    int		stopflag
)
{
	int	cmp;

	if ( root == 0 )
		return( AVL_NOMORE );

	cmp = (*fcmp)( data, root->avl_data, carg );
	if ( cmp == 0 ) {
		if ( (*fmatch)( root->avl_data, marg ) == stopflag )
			return( stopflag );

		if ( root->avl_left != 0 )
			if ( avl_prefixapply( root->avl_left, data, fmatch,
			    marg, fcmp, carg, stopflag ) == stopflag )
				return( stopflag );

		if ( root->avl_right != 0 )
			return( avl_prefixapply( root->avl_right, data, fmatch,
			    marg, fcmp, carg, stopflag ) );
		else
			return( AVL_NOMORE );

	} else if ( cmp < 0 ) {
		if ( root->avl_left != 0 )
			return( avl_prefixapply( root->avl_left, data, fmatch,
			    marg, fcmp, carg, stopflag ) );
	} else {
		if ( root->avl_right != 0 )
			return( avl_prefixapply( root->avl_right, data, fmatch,
			    marg, fcmp, carg, stopflag ) );
	}

	return( AVL_NOMORE );
}
