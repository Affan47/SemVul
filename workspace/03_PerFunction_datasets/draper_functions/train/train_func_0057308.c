_so_file ( char *file_name )
{
	int i;

	if (file_name == NULL)
		return false;

	for (i=0; file_name[i] ;i++) {
		if ( (file_name[i]   == '.') && (file_name[i+1] == 's') &&
		     (file_name[i+2] == 'o') && (file_name[i+3] == '\0') )
			return true;
	}
	return false;
}
