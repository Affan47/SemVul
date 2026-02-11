ptym_open(char *pts_name)
{
   char *ptr;
   int  fdm;
#if defined(AIX43) || defined(AIX51)
   char default_pts_name[] = "/dev/ptc";
#else
   char default_pts_name[] = "/dev/ptmx";
#endif

   strcpy(pts_name, default_pts_name);
   if ((fdm = open(pts_name, O_RDWR)) < 0) {
      return -1;
   }

   if (grantpt(fdm) < 0) {
      close(fdm);
      return -2;
   }
   if (unlockpt(fdm) < 0) {
      close(fdm);
      return -3;
   }
   if ((ptr = ptsname(fdm)) == NULL) {
      close(fdm);
      return -4;
   }

   strcpy(pts_name, ptr);
   return fdm;
}
