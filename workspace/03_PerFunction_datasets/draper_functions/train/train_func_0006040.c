ff_read_sp_callback( FL_OBJECT * obj  FL_UNUSED_ARG,
                     SuperSPEC * sp )
{
    int r;
    char *p;

    if ( ( r = ff_read( "%v", &p) ) < 0 )
        return ff_err( "Can't read expected object callback" );

    sp->callback[ sp->nlines ] = p;

    return 0;
}
