skip_input_bytes (RECSTREAM *rstrm, long cnt)
{
  int current;

  while (cnt > 0)
    {
      current = rstrm->in_boundry - rstrm->in_finger;
      if (current == 0)
	{
	  if (!fill_input_buf (rstrm))
	    return FALSE;
	  continue;
	}
      current = (cnt < current) ? cnt : current;
      rstrm->in_finger += current;
      cnt -= current;
    }
  return TRUE;
}
