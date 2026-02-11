send_gamma (Ma1509_Scanner * s)
{
  SANE_Byte cmd[0x08], *buffer;
  SANE_Status status;
  size_t total_size = MA1509_GAMMA_SIZE;
  SANE_Int color;

  buffer = malloc (total_size);
  if (!buffer)
    {
      DBG (1, "send_gamma: couldn't malloc %lu bytes for gamma  buffer\n",
	   (u_long) total_size);
      return SANE_STATUS_NO_MEM;
    }

  memset (cmd, 0, 8);
  cmd[0] = 0x2a;
  cmd[1] = 0x00;
  cmd[2] = 0x03;
  cmd[5] = (total_size >> 8) & 0xff;
  cmd[6] = total_size & 0xff;
  for (color = 1; color < 4; color++)
    {
      unsigned int i;

      if (s->val[OPT_CUSTOM_GAMMA].w)
	{
	  SANE_Int *int_buffer;

	  if (color == 1)
	    int_buffer = s->red_gamma_table;
	  else if (color == 2)
	    int_buffer = s->green_gamma_table;
	  else
	    int_buffer = s->blue_gamma_table;
	  for (i = 0; i < total_size; i++)
	    buffer[i] = int_buffer[i];
	}
      else
	{

	  for (i = 0; i < total_size; i++)
	    buffer[i] = i * 256 / total_size;
	}

      cmd[4] = color;
      status = ma1509_cmd (s, cmd, buffer, &total_size);
      if (status != SANE_STATUS_GOOD)
	{
	  DBG (1, "send_gamma: ma1509_cmd send data failed: %s\n",
	       sane_strstatus (status));
	  free (buffer);
	  return status;
	}
    }
  if (!s->val[OPT_CUSTOM_GAMMA].w)
    free (buffer);
  DBG (4, "send_gamma: done\n");
  return status;
}
