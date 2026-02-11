sendData610p (int *cmd, int len)
{
  int i, status, j;

  i = 0;
  status = 0xC8;

  while (i < len)
    {

      if (cmd[i] == 0x1B)
	status = putByte610p (0x1B);
      if (i > 0)
	{
	  if ((cmd[i] == 0xAA) && (cmd[i - 1] == 0x55))
	    status = putByte610p (0x1B);
	}

      status = putByte610p (cmd[i]);
      i++;
    }
  j = 0;
  while ((status & 0x08) && (j < 256))
    {
      status = getStatus610p ();
      j++;
    }
  if ((status != 0xC0) && (status != 0xD0))
    {
      DBG (0,
	   "sendData610p() failed, status=0x%02X, expected 0xC0 or 0xD0 (%s:%d)\n",
	   status, __FILE__, __LINE__);
      return 0;
    }


  if (i < len)
    {
      DBG (0, "sendData610p failed: sent only %d bytes out of %d (%s:%d)\n",
	   i, len, __FILE__, __LINE__);
      return 0;
    }
  return 1;
}
