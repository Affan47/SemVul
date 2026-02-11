addrharvest_set_path( AddressHarvester* harvester, const gchar *value ) {
	cm_return_if_fail( harvester != NULL );
	harvester->path = mgu_replace_string( harvester->path, value );
	g_strstrip( harvester->path );
}
