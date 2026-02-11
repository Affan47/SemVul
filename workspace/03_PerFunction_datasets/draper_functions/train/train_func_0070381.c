parse_decibel(const char *q)
{
  flag_decibel = 1;
  argc_decibel = 0;
  double lastx = 0;
  while (*q)
    {
      char *ptr;
      double x = strtod(q, &ptr);
      if (ptr == q)
        G_THROW( ERR_MSG("c44.decibel_not_number") );
      if (lastx>0 && q[-1]=='+')
        x += lastx;
      if (x<16 || x>50 || x<lastx)
        G_THROW( ERR_MSG("c44.decibel_out_of_range") );
      lastx = x;
      if (*ptr && *ptr!='+' && *ptr!=',')
        G_THROW( ERR_MSG("c44.decibel_comma_expected") );
      q = (*ptr ? ptr+1 : ptr);
      argv_decibel[argc_decibel++] = (float)x;
      if (argc_decibel>=MAXCHUNKS)
        G_THROW( ERR_MSG("c44.decibel_too_many") );
    }
  if (argc_decibel < 1)
    G_THROW( ERR_MSG("c44.decibel_no_chunks") );
}
