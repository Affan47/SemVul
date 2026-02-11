read_data(const char* fname)
{
    int    i, n;
    int    color_planes;
    char   str[20];
    FILE   *f;
    int    w, h;

    f = fopen( fname, "r");

    if ( f == NULL )
    {
        printf( "Could not open file <%s>\n", fname );
        return -1;
    }

    fscanf( f, "%s", str );
    fscanf( f, "%d", &color_planes );
    fscanf( f, "%s", str );
    fscanf( f, "%d", &h);
    fscanf( f, "%s", str );
    fscanf( f, "%d", &w);


    g_ncomps=color_planes;
    g_lenght_y=h;
    g_lenght_x=w;

    if ( g_image_data != NULL )
    {
        free( g_image_data );
        g_image_data=NULL;
    }

    g_image_data = (unsigned char*)malloc(w*h*color_planes*sizeof(unsigned char));

    for (i = 0; i < h*w*color_planes ; i++)
    {
        fscanf( f, "%d",&n );
        g_image_data[i] = (unsigned char)n;
    }
    fclose(f);

    return 1;

}
