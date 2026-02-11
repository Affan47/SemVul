resolve_quality(int npix)
{

  if (flag_bpp)
    {
      if (flag_size)
        G_THROW( ERR_MSG("c44.exclusive") );
      flag_size = flag_bpp;
      argc_size = argc_bpp;
      for (int i=0; i<argc_bpp; i++)
        argv_size[i] = (int)(npix*argv_bpp[i]/8.0+0.5);
    }

  int nchunk = 0;
  if (flag_slice && nchunk<argc_slice)
    nchunk = argc_slice;
  if (flag_size && nchunk<argc_size)
    nchunk = argc_size;
  if (flag_decibel && nchunk<argc_decibel)
    nchunk = argc_decibel;

  if (nchunk == 0)
    {
#ifdef DECIBELS_25_30_34
      nchunk = 3;
      flag_decibel = 1;
      argc_decibel = 3;
      argv_decibel[0]=25;
      argv_decibel[1]=30;
      argv_decibel[2]=34;
#else
      nchunk = 3;
      flag_slice = 1;
      argc_slice = 3;
      argv_slice[0]=74;
      argv_slice[1]=89;
      argv_slice[2]=99;
#endif
    }

  while (argc_size < nchunk)
    argv_size[argc_size++] = 0;
  while (argc_slice < nchunk)
    argv_slice[argc_slice++] = 0;
  while (argc_decibel < nchunk)
    argv_decibel[argc_decibel++] = 0.0;

  for(int i=0; i<nchunk; i++)
    {
      g().parms[i].bytes = argv_size[i];
      g().parms[i].slices = argv_slice[i];
      g().parms[i].decibels = argv_decibel[i];
    }

  return nchunk;
}
