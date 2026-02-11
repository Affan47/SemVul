onListenerException( const QString& msg )
{
  #ifndef LASTFM_MULTI_PROCESS_HACK

    LastMessageBox::critical( tr( "Plugin Listener Error" ), msg );
  #else

    m_container->statusBar()->showMessage( msg );
  #endif
}
