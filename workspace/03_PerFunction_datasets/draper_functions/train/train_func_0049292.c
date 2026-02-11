slotShufflePlaylist()
{
    m_playlistDock.data()->sortWidget()->trimToLevel();
    m_playlistDock.data()->sortWidget()->addLevel( QString( "Shuffle" ) );
}
