fileSetBufferType(int fileID, int type)
{
  int ret = 0;
  bfile_t *fileptr;

  fileptr = file_to_pointer(fileID);

  if ( fileptr )
    {
      switch (type)
	{
	case FILE_BUFTYPE_STD:
	case FILE_BUFTYPE_MMAP:
	  fileptr->bufferType = type;
	  break;
	default:
	  Error("File type %d not implemented!", type);
	}
    }

#if ! defined (HAVE_MMAP)
  if ( type == FILE_BUFTYPE_MMAP ) ret = 1;
#endif

  return (ret);
}
