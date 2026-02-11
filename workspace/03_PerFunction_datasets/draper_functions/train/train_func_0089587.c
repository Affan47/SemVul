xvsprintf (char *fmt, va_list ap)
{
  int size, nchars;
  char *buffer;
  va_list ap_copy;


  size = strlen (fmt) + 1;
  buffer = (char *)xmalloc (size);

  while (1)
    {
#if defined(va_copy)
      va_copy (ap_copy, ap);
#elif defined(__va_copy)
      __va_copy (ap_copy, ap);
#else


      ap_copy = ap;
#endif
      nchars = vsnprintf (buffer, size, fmt, ap_copy);
#if defined(va_copy) || defined(__va_copy)
      va_end (ap_copy);
#endif

      if (nchars > -1 && nchars < size)
        return buffer;
      else if (nchars > -1)
        size = nchars + 1;


      else if (size < MAX_LEGACY_SNPRINTF_SIZE)
        size *= 2;
      else
	{
	  free(buffer);
	  break;
	}


      buffer = (char *)xrealloc (buffer, size);
    }

  return xstrdup("<FAILURE>");
}
