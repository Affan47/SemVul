make_buffered_stream (fd, buffer, bufsize)
     int fd;
     char *buffer;
     size_t bufsize;
{
  BUFFERED_STREAM *bp;

  bp = (BUFFERED_STREAM *)xmalloc (sizeof (BUFFERED_STREAM));
  ALLOCATE_BUFFERS (fd);
  buffers[fd] = bp;
  bp->b_fd = fd;
  bp->b_buffer = buffer;
  bp->b_size = bufsize;
  bp->b_used = bp->b_inputp = bp->b_flag = 0;
  if (bufsize == 1)
    bp->b_flag |= B_UNBUFF;
  return (bp);
}
