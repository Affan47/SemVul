get_pv_attr_by_path( const Glib::ustring & path, unsigned int entry ) const
{
	return get_attr_by_name( lvm2_pv_cache, path, entry ) ;
}
