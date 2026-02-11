showHide()
{
    const KWindowInfo info = KWindowSystem::windowInfo( winId(), 0, 0 );
    const int currentDesktop = KWindowSystem::currentDesktop();

    if( !isVisible() )
    {
        setVisible( true );
    }
    else
    {
        if( !isMinimized() )
        {
            if( !isActiveWindow() )
            {
                KWindowSystem::setOnDesktop( winId(), currentDesktop );
                KWindowSystem::activateWindow( winId() );
            }
            else
            {
                setVisible( false );
            }
        }
        else
        {
            setWindowState( windowState() & ~Qt::WindowMinimized );
            KWindowSystem::setOnDesktop( winId(), currentDesktop );
            KWindowSystem::activateWindow( winId() );
        }
    }
}
