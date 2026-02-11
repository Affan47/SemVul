close()
{
  if (fd >= 0)
    ::close(fd);

  if (catalog != NULL)
    free(catalog);

  if (bitmap != NULL)
    free(bitmap);
}
