upmovedir (zfull, zrelative, pinfo)
     const char *zfull;
     const char *zrelative;
     pointer pinfo;
{
  const char *ztodir = (const char *) pinfo;
  char *zto;

  zto = zsysdep_in_dir (ztodir, zrelative);
  if (zto == NULL)
    usysdep_exit (FALSE);
  upmove (zfull, zto);
  ubuffree (zto);
}
