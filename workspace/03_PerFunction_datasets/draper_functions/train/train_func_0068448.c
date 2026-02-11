uv_tty_init(uv_loop_t* loop, uv_tty_t* tty, int fd, int readable) {
  uv__stream_init(loop, (uv_stream_t*)tty, UV_TTY);

  if (readable) {
    uv__nonblock(fd, 1);
    uv__stream_open((uv_stream_t*)tty, fd, UV_READABLE);
  } else {

    uv__stream_open((uv_stream_t*)tty, fd, UV_WRITABLE);
    tty->blocking = 1;
  }

  loop->counters.tty_init++;
  tty->mode = 0;
  return 0;
}
