main(int argc, char *argv[])
{
  int fds[2];
  int size;
  char *buf;
  int64_t count, i, delta;
  struct timeval start, stop;

  if (argc != 3) {
    printf ("usage: unix_thr <message-size> <message-count>\n");
    exit(1);
  }

  size = atoi(argv[1]);
  count = atol(argv[2]);

  buf = malloc(size);
  if (buf == NULL) {
    perror("malloc");
    exit(1);
  }

  printf("message size: %i octets\n", size);
  printf("message count: %lli\n", count);

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) {
    perror("socketpair");
    exit(1);
  }

  if (!fork()) {


    for (i = 0; i < count; i++) {
      if (read(fds[1], buf, size) != size) {
        perror("read");
	exit(1);
      }
    }
  } else {


    gettimeofday(&start, NULL);

    for (i = 0; i < count; i++) {
      if (write(fds[0], buf, size) != size) {
        perror("write");
        exit(1);
      }
    }

    gettimeofday(&stop, NULL);

    delta = ((stop.tv_sec - start.tv_sec) * (int64_t) 1e6 +
	     stop.tv_usec - start.tv_usec);

    printf("average throughput: %lli msg/s\n", (count * (int64_t) 1e6) / delta);
    printf("average throughput: %lli Mb/s\n", (((count * (int64_t) 1e6) / delta) * size * 8) / (int64_t) 1e6);
  }

  return 0;
}
