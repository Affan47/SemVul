create_the_forms( void )
{
    static int init;

    if ( init )
    {
        fprintf( stderr, "fd forms already initialized\n" );
        return;
    }

    init = 1;

    fd_control = create_form_control( );
    init_controlform( );
    control_init( fd_control );

    fd_attrib = create_form_attrib( );
    fd_generic_attrib = create_form_generic_attrib( );
    fd_nullattrib = create_form_nullattrib( );

    init_attribform( );

    fd_test = create_form_test( );
    init_testform( );

    fd_align = create_form_align( );
    init_align( );

    fd_resize = create_form_resize( );


    fd_help = create_form_helpform( );
    init_helpform( );
}
