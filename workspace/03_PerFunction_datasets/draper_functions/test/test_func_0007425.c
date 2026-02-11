lock(LockMode mode, bool fBlock)
{
   bool fRet(false);

   if (isOpen())
   {
      if (mode != NoLock)
      {
         if (mode != m_LockMode)
         {
            if (m_LockMode != NoLock)
               unlock();

            struct flock fl;
            fl.l_whence = SEEK_SET;
            fl.l_start = 0;
            fl.l_len = 0;
            fl.l_type = (mode == ReadLock) ? F_RDLCK : F_WRLCK;

            if (::fcntl(handle(),  fBlock ? F_SETLKW : F_SETLK, &fl) != -1)
            {
               m_LockMode = mode;
               fRet = true;
            }
            else
            {
               if (errno != EINTR && errno != EAGAIN)
                  qWarning("LockedFile::lock(): fcntl: %s", ::strerror(errno));
            }
         }
         else
            fRet = true;
      }
      else
         fRet = unlock();
   }
   else
      qWarning("LockedFile::lock(): file is not opened");

   return(fRet);
}
