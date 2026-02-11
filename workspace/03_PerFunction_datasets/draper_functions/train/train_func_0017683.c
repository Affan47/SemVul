mmc5_process (void)
{
  int32 accum;

  accum = mmc5_rectangle (&mmc5rect[0]);
  accum += mmc5_rectangle (&mmc5rect[1]);
  if (mmc5dac.enabled)
    accum += mmc5dac.output;

  return accum;
}
