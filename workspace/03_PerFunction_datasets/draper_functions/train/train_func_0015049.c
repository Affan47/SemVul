showLyricsError( const QString &error ) const
{
    DEBUG_BLOCK
    LyricsManager::self()->lyricsError( error );
}
