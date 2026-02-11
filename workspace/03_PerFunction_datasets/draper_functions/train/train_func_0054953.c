slotUnregisterWindow(QObject *obj)
{
   if (!obj)
      return;

   QMap<QObject *, WId>::Iterator it = m_windowList.find(obj);
   if (it == m_windowList.end())
      return;
   WId windowId = it.value();
   q->disconnect(it.key(), SIGNAL(destroyed(QObject*)),
                 q, SLOT(slotUnregisterWindow(QObject*)));
   m_windowList.erase( it );
   QDBusInterface("org.kde.kded", "/kded", "org.kde.kded").
       call(QDBus::NoBlock, "unregisterWindowId", qlonglong(windowId));
}
