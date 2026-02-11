pull_pump (int pullfd, int pushfd)
{
  int r;
  ring_buffer ring;

  fd_set writefds, exceptfds;
  FD_ZERO(&exceptfds);
  FD_ZERO(&writefds);
  FD_SET(pushfd, &exceptfds);
  FD_SET(pushfd, &writefds);

  ring_buffer_init(&ring);

  while (pullfd >= 0) {

    r = ring_buffer_pull(&ring, pullfd);

    if (r == 0) {

      close(pullfd);
      pullfd = -1;
    } else if (r < 0 && errno != EINTR && errno != EAGAIN) {

      perror("pull_pump read()");
      close(pullfd);
      pullfd = -1;
    }


    while (!ring_buffer_empty_p(&ring)) {

      r = ring_buffer_push(&ring, pushfd);

      if (r < 0 && errno != EAGAIN && errno != EINTR) {
        if (errno == EPIPE) {


          close(pushfd);
          close(pullfd);
          pushfd = pullfd = -1;
        } else {
          perror("pull_pump write()");
          close(pushfd);
          close(pullfd);
        }
        return;
      }


      r = select(pushfd+1, NULL, &writefds, &exceptfds, NULL);

      if (r < 0 || FD_ISSET(pushfd, &exceptfds)) {
        close(pushfd);
        close(pullfd);
        pushfd = pullfd = -1;
        return;
      }
    }
  }
  assert(pullfd < 0);
  assert(ring_buffer_empty_p(&ring));
  close(pushfd);
}
