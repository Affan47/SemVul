writecheckpoint(const char *path, ckstate *c, double t0)
{
  double t1 = now();
  printf("memory phase: %" PRIu64 " nodes, %.2f sec\n", c->count, t1 - t0);

  int fd = creat(path, 0666);
  always_assert(fd >= 0);


  Json j = Json().set("generation", ckp_gen.value())
      .set("size", c->count)
      .set("firstkey", c->startkey);
  StringAccum sa;
  msgpack::unparse(sa, j);
  checked_write(fd, sa.data(), sa.length());
  checked_write(fd, c->vals->buf, c->vals->n);

  int ret = fsync(fd);
  always_assert(ret == 0);
  ret = close(fd);
  always_assert(ret == 0);

  double t2 = now();
  c->bytes = c->vals->n;
  printf("file phase (%s): %" PRIu64 " bytes, %.2f sec, %.1f MB/sec\n",
         path,
         c->bytes,
         t2 - t1,
         (c->bytes / 1000000.0) / (t2 - t1));
}
