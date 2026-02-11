slotTriggered()
{
    int button = KMessageBox::warningContinueCancel( qobject_cast<QWidget*>( parent() ),
                            i18np( "Are you sure you want to remove this cover from the Collection?",
                                  "Are you sure you want to delete these %1 covers from the Collection?",
                                  m_albums.count() ),
                            QString(),
                            KStandardGuiItem::del() );

    if ( button == KMessageBox::Continue )
    {
        foreach( Meta::AlbumPtr album, m_albums )
        {
            if( album && album->canUpdateImage() )
                album->removeImage();
        }
        kapp->processEvents();
    }
}
