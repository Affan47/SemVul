slapi_attr_get_flags( const Slapi_Attr *a, unsigned long *flags )
{
	if ( a->a_flags == 0 && a->a_plugin == NULL ) {
	    slapi_attr_init_syntax ((Slapi_Attr *)a);
	}
	*flags = a->a_flags;
	return( 0 );
}
