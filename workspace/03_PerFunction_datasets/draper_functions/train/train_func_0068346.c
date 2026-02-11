iobuf_seek (iobuf_t a, off_t newpos)
{
  file_filter_ctx_t *b = NULL;

  if (a->directfp)
    {
      FILE *fp = a->directfp;
      if (fseeko (fp, newpos, SEEK_SET))
	{
	  log_error ("can't seek: %s\n", strerror (errno));
	  return -1;
	}
      clearerr (fp);
    }
  else
    {
      for (; a; a = a->chain)
	{
	  if (!a->chain && a->filter == file_filter)
	    {
	      b = a->filter_ov;
	      break;
	    }
	}
      if (!a)
	return -1;
#ifdef FILE_FILTER_USES_STDIO
      if (fseeko (b->fp, newpos, SEEK_SET))
	{
	  log_error ("can't fseek: %s\n", strerror (errno));
	  return -1;
	}
#else
#ifdef HAVE_W32_SYSTEM
      if (SetFilePointer (b->fp, newpos, NULL, FILE_BEGIN) == 0xffffffff)
	{
	  log_error ("SetFilePointer failed on handle %p: ec=%d\n",
		     b->fp, (int) GetLastError ());
	  return -1;
	}
#else
      if (lseek (b->fp, newpos, SEEK_SET) == (off_t) - 1)
	{
	  log_error ("can't lseek: %s\n", strerror (errno));
	  return -1;
	}
#endif
#endif
    }
  a->d.len = 0;
  a->d.start = 0;
  a->nbytes = 0;
  a->nlimit = 0;
  a->nofast &= ~1;
  a->ntotal = newpos;
  a->error = 0;

  if (a->chain)
    log_debug ("pop_filter called in iobuf_seek - please report\n");
  while (a->chain)
    pop_filter (a, a->filter, NULL);

  return 0;
}
