fsp_lock (fsp_link *link)
{
  unsigned char *out = message_new(FS_LOCK, 0, 0);
  int errors = 0;

  for (fs_segment segment = 0; segment < link->segments; ++segment) {
    unsigned int * const s = (unsigned int *) (out + 8);
    *s = segment;
    fsp_write_primary(link, out, 0);

    errors += check_message(link, link->socks1[segment], "lock(%d) failed: %s");
  }
  free(out);

  return errors;
}
