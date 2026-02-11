extend_filename( const char *base_name, const char *new_ext)
{
    char *retval;
    char *ext;
  	unsigned int len;
    const char *root;

    root = strrchr(base_name, '/');
    if ( root == NULL )  root = base_name;

    ext = strrchr(root, '.');
    if ( ext != NULL )
    {
        if ( strcasecmp(ext, new_ext) == 0 )
	{
	    ext = NULL;
	}
    }

    len = ext ? (ext - base_name) : (unsigned int)strlen(base_name) ;
    retval = safe_malloc(len+strlen(new_ext)+1, "extending file-name");
    memcpy( retval, base_name, len);
    retval[len] = 0;
    strcat(retval, new_ext);

    return( retval);
}
