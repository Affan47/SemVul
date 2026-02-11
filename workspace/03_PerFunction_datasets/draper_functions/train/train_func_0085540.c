freeMemory(FileInfo *file) {
  MemInfo *mi = &file->minfo;
  if (mi->data > (char *)0){
    munmap(mi->data, mi->size);
  }
}
