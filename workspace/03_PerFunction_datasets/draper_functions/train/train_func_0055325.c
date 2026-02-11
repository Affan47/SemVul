translate_index(int idx)
{
  int _idx;
  unsigned int a, b;

  _idx = 0;
  for (a = 0;a < DIR_BLOCKS;a++)
    {
      for (b = 0;b < 4;b++)
        {
          if (_header.offset[a] & (1 << b))
	    idx--;

          if (idx < 0)
	    return _idx;

	  _idx++;
        }
    }

  return -1;
}
