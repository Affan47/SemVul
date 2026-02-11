ClaimIRLP()
{
   int Ret = 0;
   if(flock(LockIRLPfd,LOCK_EX) != 0) {
      Ret = errno;
      LOG_ERROR(("%s: flock(LOCK_EX) failed: %s",__FUNCTION__,
                 Err2String(errno)));
   }
#ifdef __linux__
   else if(ioctl(Fd,PPCLAIM) != 0) {
      Ret = errno;
      LOG_ERROR(("%s: ioctl(PPCLAIM) failed: %s",__FUNCTION__,
                 Err2String(errno)));
      if(flock(LockIRLPfd,LOCK_UN) != 0) {
         LOG_ERROR(("%s: flock(LOCK_UN) failed: %s",__FUNCTION__,
                    Err2String(errno)));
      }
   }
#endif
   else {
      PortLocked = TRUE;
   }

   return Ret;
}
