PS_cleanup( FL_IMAGE * im )
{
    int i,
        n = im->total_frames >= 1 ? im->total_frames : 1;
    SPEC *sp = im->extra_io_info;
    char name[ 1024 ];

    if ( ! sp )
        return;

    for ( i = 1; i <= n; i++ )
    {
        fl_snprintf( name, sizeof name, "%s/%s_%d", sp->tmpdir, sp->prefix, i );
        if ( sp->verbose )
            M_err( "Cleanup", "deleting %s", name );
        remove( name );
    }

    fl_free( sp->prefix );
    fl_free( sp );
    im->extra_io_info = 0;
}
