handle_byte(int byte)
{
  static int idx = 0;
  static int crc = 0;
  static int state = 0;

  switch (state)
    {
    case 0:
      if (byte == 0x02)
	{
	  idx = 1;
	  state = 1;
	  crc = (0x80 ^ byte);
	  write_byte(byte);
	}
      break;
    case 1:
      idx++;
      crc ^= (0x80 ^ byte);
      write_byte(byte);
      if ((byte == 0x03) && (idx > 2))
	state = 2;
      break;
    case 2:
      state = 0;
      write_byte(byte);
      if (crc == byte)
	printf("\nCRC ok.\n");
      else
	printf("\nCRC ERROR: calculated %02x, in file %02x\n", crc, byte);
      set_state(STATE_NO_SYNC);
      exit(0);
      new_file();
      return;
    }

  set_state(STATE_BIT_SYNC);
}
