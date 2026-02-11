suppressedPopupMenu() {
  KMenu *m = new KMenu(0L);
  if ( d->m_openableSuppressedPopups )
      m->addAction(i18np("&Show Blocked Popup Window","&Show %1 Blocked Popup Windows", d->m_openableSuppressedPopups), this, SLOT(showSuppressedPopups()));
  QAction *a = m->addAction(i18n("Show Blocked Window Passive Popup &Notification"), this, SLOT(togglePopupPassivePopup()));
  a->setChecked(d->m_settings->jsPopupBlockerPassivePopup());
  m->addAction(i18n("&Configure JavaScript New Window Policies..."), this, SLOT(launchJSConfigDialog()));
  m->popup(QCursor::pos());
}
