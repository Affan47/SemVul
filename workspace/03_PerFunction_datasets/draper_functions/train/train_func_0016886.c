setLanguage( QString langCode )
{
    LOGL( 3, "Setting language to: " << langCode );

    m_lang = langCode;


    m_translatorApp.load( MooseUtils::dataPath( "i18n/lastfm_%1" ).arg( langCode ) );
    m_translatorQt.load( MooseUtils::dataPath( "i18n/qt_%1" ).arg( langCode ) );
}
