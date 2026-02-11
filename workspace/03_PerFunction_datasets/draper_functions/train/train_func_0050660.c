slotRosterRequestFinished ( bool success )
{
  kDebug() << success;


  kDebug () << "Setting initial presence...";
  setPresence ( m_initialPresence );
}
