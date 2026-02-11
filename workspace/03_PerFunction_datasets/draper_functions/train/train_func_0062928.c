GetMagickResourceLimit(const ResourceType type)
{
  MagickSizeType
    resource;

  resource=0;
  if (resource_semaphore == (SemaphoreInfo *) NULL)
    AcquireSemaphoreInfo(&resource_semaphore);
  LockSemaphoreInfo(resource_semaphore);
  switch (type)
  {
    case AreaResource:
    {
      resource=resource_info.area_limit;
      break;
    }
    case MemoryResource:
    {
      resource=resource_info.memory_limit;
      break;
    }
    case MapResource:
    {
      resource=resource_info.map_limit;
      break;
    }
    case DiskResource:
    {
      resource=resource_info.disk_limit;
      break;
    }
    case FileResource:
    {
      resource=resource_info.file_limit;
      break;
    }
    case ThreadResource:
    {
      resource=resource_info.thread_limit;
      break;
    }
    case TimeResource:
    {
      resource=resource_info.time_limit;
      break;
    }
    default:
      break;
  }
  UnlockSemaphoreInfo(resource_semaphore);
  return(resource);
}
