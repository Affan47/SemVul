caml_grow_file(int fd, file_offset size)
{
  char c;
  int p;


#ifdef HAS_PWRITE
  c = 0;
  p = pwrite(fd, &c, 1, size - 1);
#else


  file_offset currpos;
  currpos = lseek(fd, 0, SEEK_CUR);
  if (currpos != -1) {
    p = lseek(fd, size - 1, SEEK_SET);
    if (p != -1) {
      c = 0;
      p = write(fd, &c, 1);
      if (p != -1)
        p = lseek(fd, currpos, SEEK_SET);
    }
  }
  else p=-1;
#endif
#ifdef HAS_TRUNCATE
  if (p == -1 && errno == ESPIPE) {


    p = ftruncate(fd, size);
  }
#endif
  return p;
}
