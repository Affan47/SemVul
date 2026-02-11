init(const int fd,const bool closeme)
{
  GUTF8String retval;
  data = (char*)(-1);
#if defined(PROT_READ) && defined(MAP_SHARED)
  struct stat statbuf;
  if(!fstat(fd,&statbuf) && statbuf.st_size)
    {
      bsize=statbuf.st_size;
      data=(char *)mmap(0,statbuf.st_size,PROT_READ,MAP_SHARED,fd,0);
    }
#endif
  if(data == (char *)(-1))
    retval = ERR_MSG("ByteStream.open_fail2");
  if(closeme)
    close(fd);
  return retval;
}
