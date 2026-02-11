ifile_int4str_new_from_file (const char *filename)
{
  FILE *fp;
  ifile_int4str *ret;

  fp = fopen (filename, "r");
  if (!fp)
    ifile_error ("Couldn't open file `%s' for reading\n", filename);
  ret = ifile_int4str_new_from_fp (fp);
  fclose (fp);
  return ret;
}
