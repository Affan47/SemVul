EXTRACTOR_IPC_shared_memory_set_ (struct EXTRACTOR_SharedMemory *shm,
				  struct EXTRACTOR_Datasource *ds,
				  uint64_t off,
				  size_t size)
{
  if (-1 ==
      EXTRACTOR_datasource_seek_ (ds, off, SEEK_SET))
    {
      LOG ("Failed to set IPC memory due to seek error\n");
      return -1;
    }
  if (size > shm->shm_size)
    size = shm->shm_size;
  return EXTRACTOR_datasource_read_ (ds,
				     shm->shm_ptr,
				     size);
}
