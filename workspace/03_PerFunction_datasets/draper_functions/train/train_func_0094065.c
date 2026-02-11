slapi_sdn_isgrandparent( const Slapi_DN *parent, const Slapi_DN *child )
{
	int	rc= 0;


	if ( !slapi_sdn_isempty(child) )
	{
	    Slapi_DN childparent;
		slapi_sdn_init(&childparent);
        slapi_sdn_get_parent(child,&childparent);
		if ( !slapi_sdn_isempty(&childparent) )
		{
			Slapi_DN childchildparent;
			slapi_sdn_init(&childchildparent);
			slapi_sdn_get_parent(&childparent,&childchildparent);
			rc= (slapi_sdn_compare(parent,&childchildparent)==0);
			slapi_sdn_done(&childchildparent);
		}
		slapi_sdn_done(&childparent);
	}
	return( rc );
}
