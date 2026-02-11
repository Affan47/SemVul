get_xbm_stuff( IconInfo * in,
               FILE     * fp  FL_UNUSED_ARG )
{
    char buf[ 512 ],
         *p;

    strcpy( buf, in->filename );

    if ( ( p = strrchr( buf, '/' ) ) )
        strcpy( buf, ++p );

    if ( ( p = strrchr( buf, '.' ) ) )
        *p = '\0';

    strcat( strcpy( in->width,  buf ), "_width"  );
    strcat( strcpy( in->height, buf ), "_height" );
    strcat( strcpy( in->data,   buf ), "_bits"   );
}
