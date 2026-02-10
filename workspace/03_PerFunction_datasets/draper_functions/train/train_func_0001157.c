counterTypeToString( uint32_t properties ) {

	switch( properties & OTF_COUNTER_TYPE_BITS ) {
	CASE_RETURN( TYPE, ACC );
	CASE_RETURN( TYPE, ABS );

	default: {
		static char unknown_buffer[ 64 ];
		sprintf( unknown_buffer, "UNKNOWN <%u>",
			properties & OTF_COUNTER_TYPE_BITS );
		return unknown_buffer;
	}

	}
}
