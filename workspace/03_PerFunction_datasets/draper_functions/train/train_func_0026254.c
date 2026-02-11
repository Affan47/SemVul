run( const KUrl& u, bool _is_local )
{


    if ( !_is_local )
        return false;

    KDesktopFile cfg(u.toLocalFile());
    if ( !cfg.desktopGroup().hasKey("Type") )
    {
        QString tmp = i18n("The desktop entry file %1 "
                           "has no Type=... entry.", u.toLocalFile() );
        KMessageBoxWrapper::error( 0, tmp);
        return false;
    }


    if ( cfg.hasDeviceType() )
        return runFSDevice( u, cfg );
    else if ( cfg.hasApplicationType()
              || (cfg.readType() == "Service" && !cfg.desktopGroup().readEntry("Exec").isEmpty()))
        return runApplication( u, u.toLocalFile() );
    else if ( cfg.hasLinkType() )
        return runLink( u, cfg );

    QString tmp = i18n("The desktop entry of type\n%1\nis unknown.",  cfg.readType() );
    KMessageBoxWrapper::error( 0, tmp);

    return false;
}
