_GDF_InitDirfiles(void)
{
  int i;

  dtracevoid();

  for (i = 1; i < GDF_N_DIRFILES; ++i)
    f77dirfiles[i] = NULL;


  f77dirfiles[0] = gd_invalid_dirfile();

  f77dirfiles_initialised = 1;
  dreturnvoid();
}
