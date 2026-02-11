got_startup_info( const QString& msg_P, bool update_P )
    {
    KStartupInfoId id( msg_P );
    if( id.none())
        return;
    KStartupInfo::Data data( msg_P );
    new_startup_info_internal( id, data, update_P );
    }
