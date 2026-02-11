sg_vector_clone_into(sg_vector **dest, const sg_vector *src){

	if( !dest ) {
		RETURN_WITH_SET_ERROR( "vector", SG_ERROR_INVALID_ARGUMENT, "dest" );
	}

	if( !src ) {
		if(*dest) {
			sg_vector_free(*dest);
			*dest = NULL;
		}

		return SG_ERROR_NONE;
	}

	if(SG_ERROR_NONE != sg_prove_vector(src)) {
		RETURN_WITH_SET_ERROR( "vector", SG_ERROR_INVALID_ARGUMENT, "src" );
	}

	if( !*dest ) {
		*dest = sg_vector_clone( src );
		if( *dest )
			return SG_ERROR_NONE;
	}
	else if( ( SG_ERROR_NONE == sg_prove_vector(*dest) ) &&
		 ( SG_ERROR_NONE == sg_prove_vector_compat(*dest, src) ) &&
		 ( SG_ERROR_NONE == sg_vector_clone_into_int( dest, src ) ) ) {

		return SG_ERROR_NONE;
	}

	sg_vector_free(*dest);
	*dest = NULL;
	return sg_get_error();
}
