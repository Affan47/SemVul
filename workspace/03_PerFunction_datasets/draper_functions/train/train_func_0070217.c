ReleaseIRLP()
{
#ifdef __linux__
   if(ioctl(Fd,PPRELEASE) != 0) {
      LOG_ERROR(("%s: ioctl(PPRELEASE) failed: %s",__FUNCTION__,
                 Err2String(errno)));
   } else
#endif
   if(flock(LockIRLPfd,LOCK_UN) != 0) {
      LOG_ERROR(("%s: flock(LOCK_UN) failed: %s",__FUNCTION__,
                 Err2String(errno)));
   }
   else {
      PortLocked = FALSE;
   }
}
