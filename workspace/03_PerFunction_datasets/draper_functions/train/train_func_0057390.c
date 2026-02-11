make_dirname(const char *filepath)
{
    char *dirname;
    int  dirname_length;
    char *p;

    if ( !(p=strrchr(filepath, '/')) )
#ifdef HAVE_DRIVE_LETTERS
	if ( !(p=strrchr(filepath, '\\')) )
	    if ( !(p=strrchr(filepath, ':')) )
#endif
	      {
		return jnlib_xstrdup(".");
	      }

    dirname_length = p-filepath;
    dirname = jnlib_xmalloc(dirname_length+1);
    strncpy(dirname, filepath, dirname_length);
    dirname[dirname_length] = 0;

    return dirname;
}
