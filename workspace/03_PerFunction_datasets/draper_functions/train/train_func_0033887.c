addAddBookmarksList()
{
    if( !m_pOwner || !m_pOwner->enableOption(KBookmarkOwner::ShowAddBookmark) || !m_pOwner->supportsTabs() || !KAuthorized::authorizeKAction("bookmarks") )
        return;

    if (d->bookmarksToFolder == 0) {
        QString title = i18n( "Bookmark Tabs as Folder..." );
        d->bookmarksToFolder = new KAction( title, this );
        m_actionCollection->addAction( m_bIsRoot ? "add_bookmarks_list" : 0, d->bookmarksToFolder);
        d->bookmarksToFolder->setIcon( KIcon( "bookmark-new-list" ) );
        d->bookmarksToFolder->setHelpText( i18n( "Add a folder of bookmarks for all open tabs." ) );
        connect( d->bookmarksToFolder, SIGNAL( triggered( bool ) ), this, SLOT( slotAddBookmarksList() ) );
    }

    m_parentMenu->addAction(d->bookmarksToFolder);
}
