memRead(AbstractFile* file, void* data, size_t len) {
  MemWrapperInfo* info = (MemWrapperInfo*) (file->data);
  if(info->bufferSize < (info->offset + len)) {
    len = info->bufferSize - info->offset;
  }
  memcpy(data, (void*)((uint8_t*)(*(info->buffer)) + (uint32_t)info->offset), len);
  info->offset += (size_t)len;
  return len;
}
