copy_simple (char const *buf, size_t nread)
{
  const char *start = buf;

  do
    {
      size_t nfree = MIN (nread, output_blocksize - oc);

      memcpy (obuf + oc, start, nfree);

      nread -= nfree;
      start += nfree;
      oc += nfree;
      if (oc >= output_blocksize)
        write_output ();
    }
  while (nread != 0);
}
