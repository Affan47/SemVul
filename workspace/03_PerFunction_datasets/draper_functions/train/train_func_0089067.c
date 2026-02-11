idl_nextid( IDList *idl, ID id )
{
	NIDS	i;

	if (NULL == idl) {
		return NOID;
	}
	if ( ALLIDS( idl ) ) {
		return( ++id < idl->b_nids ? id : NOID );
	}

	for ( i = 0; i < idl->b_nids && idl->b_ids[i] < id; i++ ) {
		;
	}
	i++;

	if ( i >= idl->b_nids ) {
		return( NOID );
	} else {
		return( idl->b_ids[i] );
	}
}
