val_signbit_known_set_p (enum machine_mode mode, unsigned HOST_WIDE_INT val)
{
  unsigned int width;

  if (GET_MODE_CLASS (mode) != MODE_INT)
    return false;

  width = GET_MODE_PRECISION (mode);
  if (width == 0 || width > HOST_BITS_PER_WIDE_INT)
    return false;

  val &= (unsigned HOST_WIDE_INT) 1 << (width - 1);
  return val != 0;
}
