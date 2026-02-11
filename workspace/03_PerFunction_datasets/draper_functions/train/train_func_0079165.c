specForScript( const QString& name ) const
{
    if( !m_scripts.contains( name ) )
        return QString();
    QFileInfo info( m_scripts.value(name)->url.path() );
    const QString specPath = QString( "%1/%2.spec" ).arg( info.path(), info.completeBaseName() );
    return specPath;
}
