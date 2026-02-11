addActions()
{
  KConfigGroup config = KSharedConfig::openConfig("kbookmarkrc", KConfig::NoGlobals)->group("Bookmarks");
  bool filteredToolbar = config.readEntry( "FilteredToolbar", false );

  if (bookmark().isGroup())
  {
    addOpenFolderInTabs();
    addBookmark();

    if(filteredToolbar)
    {
        QString text = bookmark().showInToolbar() ? i18n("Hide in toolbar") : i18n("Show in toolbar");
        addAction( SmallIcon(""), text, this, SLOT( toggleShowInToolbar()));
    }

    addFolderActions();
  }
  else
  {
    if(owner())
    {
      addAction( SmallIcon("window-new"), i18n( "Open in New Window" ), this, SLOT( openInNewWindow() ) );
      addAction( SmallIcon("tab-new"), i18n( "Open in New Tab" ), this, SLOT( openInNewTab() ) );
    }
    addBookmark();

    if(filteredToolbar)
    {
        QString text = bookmark().showInToolbar() ? i18n("Hide in toolbar") : i18n("Show in toolbar");
        addAction( SmallIcon(""), text, this, SLOT( toggleShowInToolbar()));
    }

    addBookmarkActions();
  }
}
