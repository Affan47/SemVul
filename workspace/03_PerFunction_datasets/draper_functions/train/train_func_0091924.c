insertKMenu( KMenu *popup )
{
  popup->contextMenu()->addAction( i18n("Configure Shortcut...") , this , SLOT(slotSetShortcut()));

  KMainWindow *window=qobject_cast<KMainWindow*>(m_builder->widget());
  if(window)
  {
    popup->contextMenu()->addAction( m_toolbarAction );
    connect(popup, SIGNAL(aboutToShowContextMenu(KMenu*,QAction*,QMenu*)) , this, SLOT(buildToolbarAction()));
  }
}
