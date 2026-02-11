slapi_attr_flag_is_set( const Slapi_Attr *a, unsigned long flag )
{
	if ( a->a_flags == 0 && a->a_plugin == NULL ) {
	    slapi_attr_init_syntax ((Slapi_Attr *)a);
	}
	return( a->a_flags & flag );
}
