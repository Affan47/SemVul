oncrpc_iob_add_fields ( struct io_buffer *io_buf,
                               const struct oncrpc_field fields[] ) {
	size_t i;
	size_t s = 0;

	struct oncrpc_field f;

	if ( ! io_buf )
		return 0;

	for ( i = 0; fields[i].type != oncrpc_none; i++ ) {
		f = fields[i];
		switch ( f.type ) {
		case oncrpc_int32:
			s += oncrpc_iob_add_int ( io_buf, f.value.int32 );
			break;

		case oncrpc_int64:
			s += oncrpc_iob_add_int64 ( io_buf, f.value.int64 );
			break;

		case oncrpc_str:
			s += oncrpc_iob_add_string ( io_buf, f.value.str );
			break;

		case oncrpc_array:
			s += oncrpc_iob_add_array ( io_buf,
			                            f.value.array.length,
			                            f.value.array.ptr );
			break;

		case oncrpc_intarray:
			s += oncrpc_iob_add_intarray ( io_buf,
			                               f.value.intarray.length,
			                               f.value.intarray.ptr );
			break;

		case oncrpc_cred:
			s += oncrpc_iob_add_cred ( io_buf, f.value.cred);
			break;

		default:
			return s;
		}
	}

	return s;
}
