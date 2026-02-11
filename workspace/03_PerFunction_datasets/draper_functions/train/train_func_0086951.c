addrharvest_set_header(
	AddressHarvester* harvester, const gchar *name, const gboolean value )
{
	HeaderEntry *entry;

	cm_return_if_fail( harvester != NULL );
	entry = addrharvest_find( harvester, name );
	if( entry != NULL ) {
		entry->selected = value;
	}
}
