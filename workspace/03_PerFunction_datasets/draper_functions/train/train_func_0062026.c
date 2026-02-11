write_output(void *ptr, size_t size, size_t n, void *data)
{
  clamz_downloader *dl = data;
  int r;

  r = write(dl->outfd, ptr, size * n);
  if (r < 0) {
    print_error("Error writing to %s: %s", dl->filename, strerror(errno));
    return 0;
  }
  else
    return r;
}
