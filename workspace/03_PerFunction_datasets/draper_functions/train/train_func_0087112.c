startpar_getpt(void) {
  int fd = open("/dev/ptmx", O_RDWR|O_NOCTTY);

  if (fd != -1)
    {
      struct statfs fsbuf;


      if ((statfs ("/dev/pts", &fsbuf) == 0
             && fsbuf.f_type == DEVPTS_SUPER_MAGIC)
         || (statfs ("/dev", &fsbuf) == 0
             && fsbuf.f_type == DEVFS_SUPER_MAGIC))
        {

          return fd;
        }


      close (fd);
    }

  return -1;
}
