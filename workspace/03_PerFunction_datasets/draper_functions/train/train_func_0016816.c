write_output (void)
{
  rlzi->writeLock = ((rlzi->rangeSize >> 0x18) & 0xFF ? 1 : 0);
  if (!rlzi->writeLock) {
    flush_output ();
  }
}
