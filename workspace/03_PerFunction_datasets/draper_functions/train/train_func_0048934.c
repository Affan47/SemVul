rt_nvram_read (int block, int location, unsigned char *data, int bytes)
{
  int addressingbits;
  unsigned char stdbits;
  unsigned char cmdbuffer[NVR_MAX_COMMAND_SIZE];
  unsigned char *address_bits;
  unsigned char readbit_command[2];
  int cmdsize;

  if (rt_nvram_init_stdvars (block, &addressingbits, &stdbits) < 0)
    return -1;

  cmdsize = addressingbits * 2 + 7;
  address_bits = cmdbuffer + 6;

  rt_nvram_set_command_bit (cmdbuffer, 1, stdbits);
  rt_nvram_set_command_bit (cmdbuffer + 2, 1, stdbits);
  rt_nvram_set_command_bit (cmdbuffer + 4, 0, stdbits);
  rt_nvram_set_half_bit (cmdbuffer + cmdsize - 1, 0, stdbits, 0);

  rt_nvram_set_half_bit (readbit_command, 0, stdbits, 1);
  rt_nvram_set_half_bit (readbit_command + 1, 0, stdbits, 0);

  if (rt_nvram_init_command () < 0)
    return -1;

  while (bytes--)
    {
      char c = 0;
      unsigned char r;
      int i;

      rt_nvram_set_addressing_bits (address_bits, location, addressingbits,
				    stdbits);

      if (rt_nvram_enable_controller (1) < 0 ||
	  rt_send_command_immediate (RTCMD_NVRAMCONTROL, 0x1d, cmdsize,
				     cmdsize, cmdbuffer, 0, 0) < 0)
	return -1;

      for (i = 0; i < 8; ++i)
	{
	  c <<= 1;

	  if (rt_send_command_immediate
	      (RTCMD_NVRAMCONTROL, 0x1d, 2, 2, readbit_command, 0, 0) < 0
	      || rt_read_register_immediate (0x10, 1, &r) < 0)
	    return -1;
	  if (r & 0x80)
	    c |= 1;
	}
      if (rt_nvram_enable_controller (0) < 0)
	return -1;

      *data++ = c;
      ++location;
    }
  return 0;
}
