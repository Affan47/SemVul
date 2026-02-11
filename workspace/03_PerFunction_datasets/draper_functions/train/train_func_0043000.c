reset_max_width( PopUP * m )
{
    int i;
    MenuItem **item = m->item;
    char *t,
         *b;


    if ( ! m->used || m->nitems <= 0 )
        return;

    m->maxw = 0;

    for ( i = 0; i < m->nitems; i++ )
    {
        b = t = fl_strdup( item[ i ]->str );
        while ( ( b = strchr( b, '\b' ) ) )
            memmove( b, b + 1, strlen( b ) );
        m->maxw = FL_max( m->maxw,
                          fl_get_string_widthTAB( pup_font_style, pup_font_size,
                                                  t, strlen( t ) ) );
        fl_free( t );
    }

    if ( m->title && *m->title )
    {
        b = t = fl_strdup( m->title );
        while ( ( b = strchr( b, '\b' ) ) )
            memmove( b, b + 1, strlen( b ) );
        m->title_width = XTextWidth( pup_title_font_struct, t, strlen( t ) );
        fl_free( t );
    }
    else
        m->title_width = 0;

    m->cellh = pup_ascent + pup_desc + 2 * m->padh;
}
