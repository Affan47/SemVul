populateConfiguration()
{
    QString mode = Amarok::config( m_configCategory ).readEntry( "Mode" );
    setAdvancedMode( mode == QLatin1String( "Advanced" ) );

    setScheme( Amarok::config( m_configCategory ).readEntryUntranslated( "Custom Scheme" ) );

    populateFormatList();
}
