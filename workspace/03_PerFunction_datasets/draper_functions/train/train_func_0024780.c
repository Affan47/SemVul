isClient()
{
   bool fRet(false);

   if (!m_LockedFile.isLocked())
   {
      if (m_LockedFile.lock(LockedFile::WriteLock, false))
      {
         bool fIsListening(m_pServer->listen(m_strSocketName));


         if (!fIsListening && m_pServer->serverError() == QAbstractSocket::AddressInUseError)
         {
            QFile::remove(QDir::cleanPath(QDir::tempPath())+QLatin1Char('/') + m_strSocketName);
            fIsListening = m_pServer->listen(m_strSocketName);
         }

         if (!fIsListening)
            qWarning() << APPNAME << ": listen on local socket failed; " << qPrintable(m_pServer->errorString());

         QObject::connect(m_pServer, SIGNAL(newConnection()), SLOT(receiveConnection()));
      }
      else
         fRet = true;
   }

   return(fRet);
}
