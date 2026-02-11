init_std_defines( void)


{
    char    tmp[ 16];
    char    timestr[ 14];
    time_t  tvec;
    char *  tstring;

    look_and_install( "__LINE__", DEF_NOARGS_DYNAMIC - 1, null, "-1234567890");

    look_and_install( "__FILE__", DEF_NOARGS_DYNAMIC - 2, null, null);


    time( &tvec);
    tstring = ctime( &tvec);
    sprintf( timestr, "\"%.3s %c%c %.4s\"",
        tstring + 4,
        *(tstring + 8) == '0' ? ' ' : *(tstring + 8),
        *(tstring + 9),
        tstring + 20);
    look_and_install( "__DATE__", DEF_NOARGS_DYNAMIC, null, timestr);
    sprintf( timestr, "\"%.8s\"", tstring + 11);
    look_and_install( "__TIME__", DEF_NOARGS_DYNAMIC, null, timestr);

    if (! look_id( "__STDC_HOSTED__")) {


        sprintf( tmp, "%d", STDC_HOSTED);
        look_and_install( "__STDC_HOSTED__", DEF_NOARGS_PREDEF, null, tmp);
    }
#if COMPILER != GNUC
    if (cplus_val)
        return;
#endif

    if (! look_id( "__STDC__")) {
        sprintf( tmp, "%d", stdc_val);
        look_and_install( "__STDC__", DEF_NOARGS_STANDARD, null, tmp);
    }
}
