allDirectories()
{
   if (m_allDirectories.isEmpty())
     return m_allDirectories;
   m_allDirectories.sort();

   QStringList::Iterator it = m_allDirectories.begin();
   QString previous = *it++;
   for(;it != m_allDirectories.end();)
   {
#ifndef Q_OS_WIN
     if ((*it).startsWith(previous))
#else
     if ((*it).startsWith(previous, Qt::CaseInsensitive))
#endif
     {
        it = m_allDirectories.erase(it);
     }
     else
     {
        previous = *it;
        ++it;
     }
   }
   return m_allDirectories;
}
