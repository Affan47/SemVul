ps_set_font( int style,
             int size )
{
    if ( style >= FL_SHADOW_STYLE )
        style %= FL_SHADOW_STYLE;

    if ( style == cur_style && cur_size == size )
        return;

    ps_output( "%d point /%s SetFont\n", size, fnts[ style ] );
    ps_output( "/H %d point def\n", size );
    cur_style = style;
    cur_size = size;
}
