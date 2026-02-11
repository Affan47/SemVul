File_write(DOH *fo, void *buffer, int len) {
  DohFile *f = (DohFile *) ObjData(fo);
  if (f->filep) {
    int ret = (int) fwrite(buffer, 1, len, f->filep);
    int err = (ret != len) ? ferror(f->filep) : 0;
    return err ? -1 : ret;
  } else if (f->fd) {
#ifdef DOH_INTFILE
    return write(f->fd, buffer, len);
#endif
  }
  return -1;
}
