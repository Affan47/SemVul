sendMessage( const QString & serviceName, const QString & message )
{

    if ( !m_serviceBrowser->categories().contains( serviceName ) )
    {
        return i18n( "No service named %1 is currently loaded", serviceName );
    }

    ServiceBase * service = dynamic_cast<ServiceBase *>( m_serviceBrowser->categories().value( serviceName ) );

    if ( service == 0 )
        return QString();

    return service->sendMessage( message );
}
