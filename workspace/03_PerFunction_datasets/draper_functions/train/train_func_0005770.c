slapi_sdn_get_backend_parent( const Slapi_DN *sdn,
	Slapi_DN *sdn_parent,
	const Slapi_Backend *backend )
{
	slapi_sdn_get_ndn( sdn );

	if ( backend == NULL ||
	     be_issuffix( (Slapi_Backend *)backend, (struct berval *)&sdn->ndn ) == 0 ) {
		slapi_sdn_get_parent( sdn, sdn_parent );
	}

}
