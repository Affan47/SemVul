uncompress_file(char *filename)
{
  char *temp_fn, randstr[5];
  int ret;


  temp_fn = nmalloc(strlen(filename) + 5);
  make_rand_str(randstr, 4);
  strcpy(temp_fn, filename);
  strcat(temp_fn, randstr);


  ret = uncompress_to_file(filename, temp_fn);


  if (ret == COMPF_SUCCESS)
    movefile(temp_fn, filename);

  nfree(temp_fn);
  return ret;
}
