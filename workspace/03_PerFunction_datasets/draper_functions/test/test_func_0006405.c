dw_FileError(int err, char *filename)
{
  char *msg, *fmt;
  if (filename)
    {
      switch(err)
	{
	case FILE_ERR:
	  fmt="File operation error on %s"; break;
	case FILE_OPEN_ERR:
	  fmt="Unable to open/create %s"; break;
	case FILE_READ_WRITE_ERR:
	  fmt="Unable to read/write %s"; break;
	default:
	  return dw_SetError(UNKNOWN_ERR,(char*)NULL);
	}
      sprintf(msg=dw_malloc(strlen(fmt)+strlen(filename)-1),fmt,filename);
      err=dw_SetError(err,msg);
      dw_free(msg);
      return err;
    }
  else
    switch(err)
      {
      case FILE_ERR:
      case FILE_OPEN_ERR:
      case FILE_READ_WRITE_ERR:
	return dw_SetError(err,(char*)NULL);
      default:
	return dw_SetError(UNKNOWN_ERR,(char*)NULL);
      }
}
