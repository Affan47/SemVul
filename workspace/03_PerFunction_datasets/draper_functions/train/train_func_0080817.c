Parse()
{
    Reset();

    int n = ReadHeader();

    if ( n <= 0 )
    {
        mf_error ( "No Tracks" );
        return false;
    }

    for ( cur_track = 0; cur_track < n; cur_track++ )
    {
        ReadTrack();

        if ( abort_parse )
        {
            return false;
        }
    }

    return true;
}
