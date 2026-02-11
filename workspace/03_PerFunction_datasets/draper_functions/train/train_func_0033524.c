probePS2 (unsigned char *dest)
{
  int i, tmp;


  for (i = 0; i < 256; i++)
    {
      WRITESLOW (0x0A, i);
      SLOWNIBBLEREGISTERREAD (0x0A, i);
      WRITESLOW (0x0A, 0xFF - i);
      SLOWNIBBLEREGISTERREAD (0x0A, 0xFF - i);
    }


  WRITESLOW (0x13, 0x01);
  WRITESLOW (0x13, 0x00);
  WRITESLOW (0x0A, 0x11);
  for (i = 0; i < 10; i++)
    {
      PS2bufferRead (0x400, dest);
      DBG (16, "Loop %d: PS2bufferRead passed ... (%s:%d)\n", i, __FILE__,
	   __LINE__);
    }


  for (i = 0; i < 10; i++)
    {
      PS2bufferWrite (0x400, dest);
      DBG (16, "Loop %d: PS2bufferWrite passed ... (%s:%d)\n", i, __FILE__,
	   __LINE__);
    }

  SLOWNIBBLEREGISTERREAD (0x0C, 0x04);
  WRITESLOW (0x13, 0x01);
  WRITESLOW (0x13, 0x00);
  WRITESLOW (0x0A, 0x18);

  return 1;
}
