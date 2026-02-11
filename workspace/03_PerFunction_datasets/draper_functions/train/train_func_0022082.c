fsp_canupload(FSP_SESSION *s,const char *fname)
{
  char *dir;
  unsigned char dirpro;
  int rc;
  struct stat sb;

  dir=directoryfromfilename(fname);
  if(dir == NULL)
  {
      errno = ENOMEM;
      return -1;
  }

  rc=fsp_getpro(s,dir,&dirpro);
  free(dir);

  if(rc)
  {
      return -1;
  }

  if(dirpro & FSP_DIR_OWNER)
      return 0;

  if( ! (dirpro & FSP_DIR_ADD))
      return -1;

  if (dirpro & FSP_DIR_DEL)
     return 0;


  rc = fsp_stat(s,fname,&sb);

  if (rc == 0)
      return -1;
  else
      return 0;
}
