flimage_write_annotation( FL_IMAGE * im )
{
    FILE *fp;
    int i;
    FLIMAGE_MARKER *m;
    FLIMAGE_TEXT *t;

    if ( !im || im->type == FL_IMAGE_NONE )
        return -1;

    fp = im->fpout;


    if ( im->nmarkers )
    {
        fprintf( fp, "\n###markers %d %d\n", im->nmarkers, MARKERVERSION );
        fprintf( fp, "# name x y w h fill angle thick style r g b r g b\n" );
        m = im->marker;
        for ( i = 0; i < im->nmarkers; i++, m++ )
            write_marker( m, fp );
    }

    if ( im->ntext )
    {
        fprintf( fp, "###text %d %d\n", im->ntext, TEXTVERSION );
        fprintf( fp, "# (s) font style size x y align angle nobk "
                 "r g b r g b\n" );
        t = im->text;
        for ( i = 0; i < im->ntext; i++, t++ )
            write_text( t, fp );
    }

    return 0;
}
