ec_read_file_func (voidpf opaque,
		   void* buf,
		   uLong size)
{
  struct EXTRACTOR_ExtractContext *ec = opaque;
  void *ptr;
  ssize_t ret;
  uLong done;

  done = 0;
  while (done < size)
    {
      ret = ec->read (ec->cls,
		      &ptr,
		      size);
      if (ret <= 0)
	return done;
      memcpy (buf + done, ptr, ret);
      done += ret;
    }
  return done;
}
