caml_input_scan_line(struct channel *channel)
{
  char * p;
  int n;

  p = channel->curr;
  do {
    if (p >= channel->max) {

      if (channel->curr > channel->buff) {


        memmove(channel->buff, channel->curr, channel->max - channel->curr);
        n = channel->curr - channel->buff;
        channel->curr -= n;
        channel->max -= n;
        p -= n;
      }
      if (channel->max >= channel->end) {


        return -(channel->max - channel->curr);
      }

      n = caml_do_read(channel->fd, channel->max, channel->end - channel->max);
      if (n == 0) {


        return -(channel->max - channel->curr);
      }
      channel->offset += n;
      channel->max += n;
    }
  } while (*p++ != '\n');

  return (p - channel->curr);
}
