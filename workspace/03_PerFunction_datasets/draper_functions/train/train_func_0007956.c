loadSvg( const QString& name )
{
    const QString &svgFilename = !m_customTheme ? KStandardDirs::locate( "data", name ) : name;
    QSvgRenderer *renderer = new QSvgRenderer( The::svgTinter()->tint( svgFilename ) );

    if ( !renderer->isValid() )
    {
        debug() << "Bluddy 'ell mateys, aye canna' load ya Ess Vee Gee at " << svgFilename;
        delete renderer;
        return false;
    }
    QWriteLocker writeLocker( &m_lock );

    if( m_renderers[name] )
        delete m_renderers[name];

    m_renderers[name] = renderer;
    return true;
}
