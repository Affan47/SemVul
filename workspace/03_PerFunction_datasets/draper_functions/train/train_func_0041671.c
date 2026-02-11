soxr_set_num_channels(soxr_t p, unsigned num_channels)
{
  if (!p)                return "invalid soxr_t pointer";
  if (num_channels == p->num_channels) return p->error;
  if (!num_channels)     return "invalid # of channels";
  if (p->resamplers)     return "# of channels can't be changed";
  p->num_channels = num_channels;
  return soxr_set_io_ratio(p, p->io_ratio, 0);
}
