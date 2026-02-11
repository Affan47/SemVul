be_issuffix(
    Backend *be,
    struct berval *bvsuffix )
{
	int	i;

	if ( be->be_nsuffix == NULL ) {
		return 0;
	}

	for ( i = 0; !BER_BVISNULL( &be->be_nsuffix[i] ); i++ ) {
		if ( bvmatch( &be->be_nsuffix[i], bvsuffix ) ) {
			return 1;
		}
	}

	return 0;
}
