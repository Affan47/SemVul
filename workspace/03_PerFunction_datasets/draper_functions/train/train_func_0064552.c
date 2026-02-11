File_read(DOH *fo, void *buffer, int len) {
  DohFile *f = (DohFile *) ObjData(fo);

  if (f->filep) {
    return fread(buffer, 1, len, f->filep);
  } else if (f->fd) {
#ifdef DOH_INTFILE
    return read(f->fd, buffer, len);
#endif
  }
  return -1;
}
