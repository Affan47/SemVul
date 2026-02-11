low_write_all_regs (SANE_Int devnum, SANE_Byte * regs)
{
  int i;
  SANE_Status status;
  size_t size;
  static SANE_Byte command_block1[0xb7];
  static SANE_Byte command_block2[0x4f];
  command_block1[0] = 0x88;
  command_block1[1] = 0x00;
  command_block1[2] = 0x00;
  command_block1[3] = 0xb3;
  for (i = 0; i < 0xb3; i++)
    {
      command_block1[i + 4] = regs[i];
    }
  command_block2[0] = 0x88;
  command_block2[1] = 0xb4;
  command_block2[2] = 0x00;
  command_block2[3] = 0x4b;
  for (i = 0; i < 0x4b; i++)
    {
      command_block2[i + 4] = regs[i + 0xb4];
    }
  size = 0xb7;

#ifdef DEEP_DEBUG
  fprintf (stderr, "write_all(0x00,255)=");
  for (i = 0; i < 255; i++)
    {
      fprintf (stderr, "0x%02x ", regs[i]);
    }
  fprintf (stderr, "\n");
#endif

  status = low_usb_bulk_write (devnum, command_block1, &size);
  if (status != SANE_STATUS_GOOD)
    return status;
  size = 0x4f;
  status = low_usb_bulk_write (devnum, command_block2, &size);
  if (status != SANE_STATUS_GOOD)
    return status;
  return SANE_STATUS_GOOD;
}
