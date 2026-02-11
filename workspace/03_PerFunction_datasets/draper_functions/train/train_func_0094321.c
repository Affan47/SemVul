copy_hes_fields( byte const* in, track_info_t* out )
{
	if ( *in >= ' ' )
	{
		in = copy_field( in, out->game );
		in = copy_field( in, out->author );
		in = copy_field( in, out->copyright );
	}
}
