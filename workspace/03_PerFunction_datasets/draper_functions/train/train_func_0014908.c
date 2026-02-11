plugrack_set_major_type( plugrack_t rack, const char *type )
{
	if ( ! rack )
		return SLURM_ERROR;
	if ( ! type )
		return SLURM_ERROR;


	xfree( rack->major_type );


	if ( type != NULL ) {
		rack->major_type = xstrdup( type );
		if ( rack->major_type == NULL ) {
			debug3( "plugrack_set_major_type: unable to set type");
			return SLURM_ERROR;
		}
	}

	return SLURM_SUCCESS;
}
