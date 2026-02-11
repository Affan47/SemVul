closeEvent( QCloseEvent *e )
{
#ifdef Q_WS_MAC
    Q_UNUSED( e );
    hide();
#else


    if( AmarokConfig::showTrayIcon() && e->spontaneous() && !kapp->sessionSaving() )
    {
        KMessageBox::information( this,
                i18n( "<qt>Closing the main window will keep Amarok running in the System Tray. "
                      "Use <B>Quit</B> from the menu, or the Amarok tray icon to exit the application.</qt>" ),
                i18n( "Docking in System Tray" ), "hideOnCloseInfo" );

        hide();
        e->ignore();
        return;
    }

    e->accept();
    App::instance()->quit();
#endif
}
