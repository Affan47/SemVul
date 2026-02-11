cmfopen( filename, mode, major_version,minor_version)
     char *filename;
     char *mode;

     int major_version;
     int minor_version;
{
  char syspath[MYMAXNAMLEN];
  Af_key key;
  FILE *fp;

  if (strrchr(filename,'/') == NIL)
    strcpy(syspath,curvpath[0]);
  else
    strcpy(syspath,af_afpath(filename));

  if(af_crkey(syspath, af_afname(filename), af_aftype (filename),&key) == -1)
    errexit(10,"af_crkey");
  else
    {
      fp = af_open(&key, mode);
      return (fp);
    }
  return((FILE *) NIL);
}
