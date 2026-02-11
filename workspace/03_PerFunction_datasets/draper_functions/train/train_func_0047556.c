zterp_io_read32(const zterp_io *io, uint32_t *v)
{
  uint8_t buf[4];

  if(zterp_io_read(io, buf, sizeof buf) != sizeof buf) return 0;

  *v = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];

  return 1;
}
