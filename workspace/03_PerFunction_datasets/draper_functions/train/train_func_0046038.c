__strerror_r (int errnum, char *buf, size_t buflen)
{
  if (__builtin_expect (errnum < 0 || errnum >= _sys_nerr_internal
			|| _sys_errlist_internal[errnum] == NULL, 0))
    {


      char numbuf[21];
      const char *unk = _("Unknown error ");
      size_t unklen = strlen (unk);
      char *p, *q;
      bool negative = errnum < 0;

      numbuf[20] = '\0';
      p = _itoa_word (abs (errnum), &numbuf[20], 10, 0);


      q = __mempcpy (buf, unk, MIN (unklen, buflen));
      if (negative && unklen < buflen)
	{
	  *q++ = '-';
	  ++unklen;
	}
      if (unklen < buflen)
	memcpy (q, p, MIN ((size_t) (&numbuf[21] - p), buflen - unklen));


      if (buflen > 0)
	buf[buflen - 1] = '\0';

      return buf;
    }

  return (char *) _(_sys_errlist_internal[errnum]);
}
