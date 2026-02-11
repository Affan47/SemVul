twiddler_console(char *s)
{
   int consolenr = atoi(s);
   int fd;
   if (consolenr == 0) return 0;

   fd=open_console(O_RDONLY);
   if (fd < 0) return -1;
   if (ioctl(fd, VT_ACTIVATE, consolenr)<0) {close(fd); return -1;}

   close(fd);
   return 0;
}
