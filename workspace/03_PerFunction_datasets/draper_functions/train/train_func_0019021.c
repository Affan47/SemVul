preload(void)
{
  while (lowbits>=8)
    {
      if (bufpos >= bufmax)
	{

	  bufpos = bufmax = 0;
          int size = sizeof(buffer);
          if (readmax>=0 && readmax<size)
            size = readmax;
          if (size>0)
            bufmax = inp.read((void*)buffer, size);
          readmax -= bufmax;
	  if (bufmax <= 0)
            return;
	}
      lowbits -= 8;
      codeword |= buffer[bufpos++] << lowbits;
    }
}
