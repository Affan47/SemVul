netio_tap_open(char *tap_devname)
{
#ifdef __linux__
   struct ifreq ifr;
   int fd,err;

   if ((fd = open("/dev/net/tun",O_RDWR)) < 0)
      return(-1);

   memset(&ifr,0,sizeof(ifr));


   ifr.ifr_flags = IFF_TAP|IFF_NO_PI;
   if (*tap_devname)
      strncpy(ifr.ifr_name,tap_devname,IFNAMSIZ);

   if ((err = ioctl(fd,TUNSETIFF,(void *)&ifr)) < 0) {
      close(fd);
      return err;
   }

   strcpy(tap_devname,ifr.ifr_name);
   return(fd);
#else
   int i,fd = -1;

   if (*tap_devname) {
      fd = open(tap_devname,O_RDWR);
   } else {
      for(i=0;i<16;i++) {
         snprintf(tap_devname,NETIO_DEV_MAXLEN,"/dev/tap%d",i);

         if ((fd = open(tap_devname,O_RDWR)) >= 0)
            break;
      }
   }

   return(fd);
#endif
}
