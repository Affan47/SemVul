buffering_write(int fd, char *buffer, long num)
{
  if (fd != bw_fd) {

    if (bw_fd >= 0 && bw_pos > 0) {
      if (blocking_write(bw_fd, bw_outbuf, bw_pos)) {
	perror("write (in buffering_write, flushing)");
      }
    }
    bw_fd  = fd;
    bw_pos = 0;
  }

  if (bw_pos + num > OUTBUFSZ) {

    memcpy(&bw_outbuf[bw_pos], buffer, OUTBUFSZ - bw_pos);
    if (blocking_write(fd, bw_outbuf, OUTBUFSZ)) {
      perror("write (in buffering_write, full buffer)");
      return(-1);
    }
    num -= (OUTBUFSZ - bw_pos);
    buffer += (OUTBUFSZ - bw_pos);
    bw_pos = 0;
  }

  memcpy(&bw_outbuf[bw_pos], buffer, num);
  bw_pos += num;

  return(0);
}
