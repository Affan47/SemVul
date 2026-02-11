init()
{
    setText( i18np("Unset Cover", "Unset Covers", m_albums.count()) );
    setIcon( KIcon("list-remove") );
    setToolTip( i18np("Remove artwork for this album", "Remove artwork for %1 albums", m_albums.count()) );


    bool enabled = false;
    foreach( Meta::AlbumPtr album, m_albums )
        enabled |= ( album->hasImage() && album->canUpdateImage() );
    setEnabled( enabled );
}
