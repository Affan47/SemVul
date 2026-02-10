createPidFile()
{
   bool fRet(false);

   if (pidFile.open(QIODevice::ReadWrite))
   {
      const QByteArray abPid(pidFile.readAll());
      pidFile.close();

      const int iPid(abPid.count() == 0 ? 0 : abPid.toInt());

      if (!iPid || iPid == ::getpid() || ::kill(iPid, 0) != 0)
      {
         if (::setsid() >= 0)
         {
            if (pidFile.remove())
            {
               if (pidFile.open(QIODevice::WriteOnly))
               {
                  pidFile.write((QString::number(::getpid()) + '\n').toLatin1());
                  pidFile.close();
                  fRet = true;
               }
               else
                  ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to open pid file: %s", pidFile.fileName().toAscii().constData());
            }
            else
               ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to unlink pid file: %s", pidFile.fileName().toAscii().constData());
         }
         else
            ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to set SID: %m");
      }
      else
         ::syslog(LOG_CRIT|LOG_DAEMON, "There's already a %s running", KEY);
   }
   else
      ::syslog(LOG_CRIT|LOG_DAEMON, "Failed to read pid file %s", pidFile.fileName().toAscii().constData());

   return(fRet);
}
