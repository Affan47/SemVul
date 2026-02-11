gw_db_file_is_real_file ( GWDBFile *file) {
	if ( file != NULL ) {
		return ( (S_IFMT & file->rights) != S_IFDIR && (S_IFMT & file->rights) != S_IFCHR && (S_IFMT & file->rights) != S_IFIFO && (S_IFMT & file->rights) != S_IFSOCK);
	}


	return FALSE;
}
