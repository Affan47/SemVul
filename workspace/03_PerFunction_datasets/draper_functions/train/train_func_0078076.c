gap_lib_file_copy(char *fname, char *fname_copy)
{
  FILE        *l_fp;
  char                     *l_buffer;
  struct stat               l_stat_buf;
  long         l_len;

  if(gap_debug) printf("gap_lib_file_copy src:%s dst:%s\n", fname, fname_copy);


  if (0 != g_stat(fname, &l_stat_buf))
  {
    fprintf (stderr, "stat error on '%s'\n", fname);
    return -1;
  }
  l_len = (long)l_stat_buf.st_size;


  l_buffer=(char *)g_malloc0((size_t)l_len+1);
  if(l_buffer == NULL)
  {
    fprintf(stderr, "file_copy: calloc error (%ld Bytes not available)\n", l_len);
    return -1;
  }


  l_fp = g_fopen(fname, "rb");
  if(l_fp == NULL)
  {
    fprintf (stderr, "open(read) error on '%s'\n", fname);
    g_free(l_buffer);
    return -1;
  }
  fread(l_buffer, 1, (size_t)l_len, l_fp);
  fclose(l_fp);

  l_fp = g_fopen(fname_copy, "wb");
  if(l_fp == NULL)
  {
    fprintf (stderr, "file_copy: open(write) error on '%s' \n", fname_copy);
    g_free(l_buffer);
    return -1;
  }

  if(l_len > 0)
  {
     fwrite(l_buffer,  l_len, 1, l_fp);
  }

  fclose(l_fp);
  g_free(l_buffer);
  return 0;
}
