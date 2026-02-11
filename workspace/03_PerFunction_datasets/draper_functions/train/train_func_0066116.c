open_file_get_length(
		const char *filename,
		const char *otype, int *size)
{
	FILE *tf = fopen( filename, otype );
	if ( tf == NULL ) {
		return NULL;
	}
	if ( size != NULL ) {
		fseek( tf, 0, SEEK_END );
		*size = ftell( tf );
		fseek( tf, 0, SEEK_SET );
	}
	return tf;
}
