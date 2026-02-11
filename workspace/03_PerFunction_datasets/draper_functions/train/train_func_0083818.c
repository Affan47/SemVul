showMenubar(const QObject *recvr, const char *slot, QObject *parent)
{
  KToggleAction *ret = new KToggleAction(i18n( "Show &Menubar" ), parent);
  ret->setObjectName(name(ShowMenubar));
  ret->setIcon( KIcon( "show-menu" ) );

  ret->setShortcut( KStandardShortcut::shortcut( KStandardShortcut::ShowMenubar ) );

  ret->setWhatsThis( i18n( "Show Menubar<p>"
                           "Shows the menubar again after it has been hidden</p>" ) );

  ret->setChecked( true );

  if ( recvr && slot )
    QObject::connect( ret, SIGNAL(triggered(bool)), recvr, slot );

  KActionCollection *collection = qobject_cast<KActionCollection *>(parent);
  if (collection)
    collection->addAction(ret->objectName(), ret);

  return ret;
}
