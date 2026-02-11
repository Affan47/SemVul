read_data( const char* fname,
                      int ndims,
                      hsize_t *dims,
                      float **buf )
{
    int      i, n;
    unsigned j;
    char     str[20];
    size_t   nelms;
    FILE     *f;
    float    val;
    char     *srcdir = getenv("srcdir");
    char     data_file[512];

    HDstrcpy(data_file, "");

    if(srcdir)
    {
        HDstrcpy(data_file, srcdir);
        HDstrcat(data_file, "/");
    }

    HDstrcat(data_file,fname);

    f = HDfopen(data_file, "r");
    if( f == NULL ) {
        printf( "Could not open file %s\n", data_file );
        return -1;
    }

    for(i=0, nelms=1; i < ndims; i++) {
        fscanf( f, "%s %u", str, &j);
        fscanf( f, "%d",&n );
        dims[i] = n;
        nelms *= n;
    }

    *buf = (float*) HDmalloc (nelms * sizeof( float ));

    if ( *buf == NULL ) {
        printf( "memory allocation failed\n" );
        HDfclose(f);
        return -1;
    }

    for(j = 0; j < nelms; j++) {
        fscanf( f, "%f",&val );
        (*buf)[j] = val;
    }
    HDfclose(f);

    return 1;

}
