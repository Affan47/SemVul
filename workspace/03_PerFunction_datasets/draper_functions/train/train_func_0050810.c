memFileWrite(AbstractFile* file, const void* data, size_t len) {
  MemFileWrapperInfo* info = (MemFileWrapperInfo*) (file->data);

  while((info->offset + (size_t)len) > info->actualBufferSize) {
		info->actualBufferSize <<= 1;
    *(info->buffer) = realloc(*(info->buffer), info->actualBufferSize);
  }

  if((info->offset + (size_t)len) > (*(info->bufferSize))) {
		memset(((uint8_t*)(*(info->buffer))) + *(info->bufferSize), 0, (info->offset + (size_t)len) - *(info->bufferSize));
		*(info->bufferSize) = info->offset + (size_t)len;
	}

  memcpy((void*)((uint8_t*)(*(info->buffer)) + (uint32_t)info->offset), data, len);
  info->offset += (size_t)len;
  return len;
}
