next_selection( void )
{
    if ( ! cur_form || ! BackOBJ( ) )
        return;

    do
    {
        if ( ! selnumb || ! selobj[ 0 ]->next )
            selobj[ 0 ] = BackOBJ( )->next ? BackOBJ( )->next : BackOBJ( );
        else if ( selnumb && selobj[ 0 ]->next )
            selobj[ 0 ] = selobj[ 0 ]->next;

    } while ( selobj[ 0 ]->parent );

    selnumb = 1;
    redraw_the_form( 0 );
}
