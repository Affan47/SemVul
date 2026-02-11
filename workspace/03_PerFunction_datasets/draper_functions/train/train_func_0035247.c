fsp_write_replica_locked(fsp_link* link, const void *data, size_t size)
{
  unsigned int * const s = (unsigned int *) (data + 8);
  fs_segment segment = *s;

#ifdef FS_PROFILE_WRITE
  struct timeval start, stop;

  gettimeofday(&start, NULL);
#endif

  if (write(link->socks1[segment], data, FS_HEADER + size) == -1) {
    if (errno != EPIPE) {
      link_error(LOG_ERR, "write_replica(%d) failed: %s", segment, strerror(errno));
    }
  } else if (link->socks2[segment] != -1) {

    write(link->socks2[segment], data, FS_HEADER + size);
  }
#ifdef FS_PROFILE_WRITE
  gettimeofday(&stop, NULL);

  link->tics[segment] += (stop.tv_sec - start.tv_sec) * 1000;
  link->tics[segment] += (stop.tv_usec - start.tv_usec) / 1000;
#endif
}
