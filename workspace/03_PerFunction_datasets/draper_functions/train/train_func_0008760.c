f_jptty(int mode, DrawItem *self, int uid)
{
   int i,fd;

   switch (mode) {
      case F_CREATE:
      case F_POST: break;
      case F_INVOKE:
         i=atoi(self->arg);
         fd=open(consolename,O_RDWR);
         if (fd<0) {
            gpm_report(GPM_PR_ERR, "%s: %s",consolename, strerror(errno));
            return 1;
         }
         if (ioctl(fd, VT_ACTIVATE, i)<0) {
            gpm_report(GPM_PR_ERR, "%s: %s", consolename,strerror(errno));
            return 1;
         }
         if (ioctl(fd, VT_WAITACTIVE, i)<0) {
            gpm_report(GPM_PR_ERR, "%s: %s", consolename,strerror(errno));
            return 1;
         }
      default: return 0;
   }
   return 0;
}
