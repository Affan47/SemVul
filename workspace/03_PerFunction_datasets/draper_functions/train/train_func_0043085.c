fl_set_xyplot_xtics( FL_OBJECT * ob,
                     int         major,
                     int         minor )
{
    FLI_XYPLOT_SPEC *sp = ob->spec;
    int ma = major ? major : XMAJOR;
    int mi = minor ? minor : XMINOR;

    if ( major > MAX_MAJOR )
        major = MAX_MAJOR;

    if ( minor > MAX_MINOR )
        minor = MAX_MINOR;

    if ( major * minor >= MAX_TIC )
    {
        M_err( "fl_set_xyplot_xtics",
               "major * minor should be less than %d", MAX_TIC );
        minor = 5;
        major = 10;
    }

    if ( sp->xmajor != ma || sp->xminor != mi )
    {


        sp->xmajor = major ? major : XMAJOR;
        sp->xminor = minor ? minor : XMINOR;
        if ( *sp->axtic )
            free_atic( sp->axtic );
        fl_redraw_object( ob );
    }
}
