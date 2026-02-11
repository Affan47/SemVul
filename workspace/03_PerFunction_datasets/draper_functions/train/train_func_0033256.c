destroy_avps( unsigned short flags, int_str name, int all)
{
	struct usr_avp *avp;
	int n;

	n = 0;
	while ( (avp=search_first_avp( flags, name, 0, 0))!=0 ) {
		destroy_avp( avp );
		n++;
		if ( !all )
			break;
	}
	return n;
}
