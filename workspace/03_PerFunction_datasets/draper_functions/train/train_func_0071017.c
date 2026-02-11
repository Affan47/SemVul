showStatusbar(const QObject *recvr, const char *slot, QObject *parent)
{
  KToggleAction *ret = new KToggleAction(i18n( "Show St&atusbar" ), parent);
  ret->setObjectName(name(ShowStatusbar));

  ret->setWhatsThis( i18n( "Show Statusbar<p>"
                           "Shows the statusbar, which is the bar at the bottom of the window used for status information.</p>" ) );

  ret->setChecked( true );

  if ( recvr && slot )
    QObject::connect( ret, SIGNAL(triggered(bool)), recvr, slot );

  KActionCollection *collection = qobject_cast<KActionCollection *>(parent);
  if (collection)
    collection->addAction(ret->objectName(), ret);

  return ret;
}
