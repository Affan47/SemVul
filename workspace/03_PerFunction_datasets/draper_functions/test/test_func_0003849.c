newFolder( const QString & text, bool, const QString & )
{
  QString _text = KStringHandler::csqueeze(text).replace( '&', "&&" );
  KActionMenu * actionMenu = new KImportedBookmarkActionMenu( KIcon("folder"), _text, this );
  mstack.top()->parentMenu()->addAction(actionMenu);
  mstack.top()->m_actions.append( actionMenu );
  KImportedBookmarkMenu *subMenu = new KImportedBookmarkMenu( m_pManager, m_menu->owner(), actionMenu->menu());
  mstack.top()->m_lstSubMenus.append( subMenu );

  mstack.push(subMenu);
}
