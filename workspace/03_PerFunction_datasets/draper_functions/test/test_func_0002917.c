get( int index ) const
{
	SP_Sid_t ret = { 0, 0 };

	SP_Sid_t * p = (SP_Sid_t*)mList->getItem( index );
	if( NULL != p ) ret = *p;

	return ret;
}
