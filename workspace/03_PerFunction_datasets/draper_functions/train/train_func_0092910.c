InitLog( const char *log_name, struct s_Clock *log_clock ) {
    Log = fopen( log_name, "w" );

    if( !Log ) {
        log_err( "Error while opening log \"%s\"", log_name );
        return 0;
    }

    LogOpened = true;
    LogClock = log_clock;

    str16 time;
    str64 date;
    GetTime( date, 64, DateFmt );
    GetTime( time, 16, TimeFmt );
    strncat( date, " - ", 3 );
    strncat( date, time, 16 );

    WriteLog( "Byte-Project Log v%d.%d.%d\n", BYTE_MAJOR, BYTE_MINOR, BYTE_PATCH );
    WriteLog( "%s\n", date );
    WriteLog( "==========================\n" );

    return 1;
}
