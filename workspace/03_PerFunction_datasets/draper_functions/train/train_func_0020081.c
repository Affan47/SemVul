show_selection( void )
{
    int i;

    if ( backf )
        return;

    if ( ! cur_form )
        return;

    for ( i = 0; i < selnumb; i++ )
        fl_show_object( selobj[ i ] );
}
