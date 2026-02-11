empty_ctnr(CONTAINER rootNode)
{
	INDEX i;

	if (rootNode == NIL) {
		rpterr("empty_ctnr: NIL argument");
		return;
	}

	for ( i = level_ctnr( rootNode ); i >= 0; --i )
		free( pop_ctnr( rootNode ) );

	return;
}
