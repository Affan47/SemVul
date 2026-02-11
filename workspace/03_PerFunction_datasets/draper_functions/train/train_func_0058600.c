gap_lib_alloc_fname_fixed_digits(char *basename, long nr, char *extension, long digits)
{
  gchar *l_fname;
  gint   l_len;

  if(basename == NULL) return (NULL);
  l_len = (strlen(basename)  + strlen(extension) + 10);
  l_fname = (char *)g_malloc(l_len);

  switch(digits)
  {
    case 8:  l_fname = g_strdup_printf("%s%08ld%s", basename, nr, extension);
             break;
    case 7:  l_fname = g_strdup_printf("%s%07ld%s", basename, nr, extension);
             break;
    case 6:  l_fname = g_strdup_printf("%s%06ld%s", basename, nr, extension);
             break;
    case 5:  l_fname = g_strdup_printf("%s%05ld%s", basename, nr, extension);
             break;
    case 4:  l_fname = g_strdup_printf("%s%04ld%s", basename, nr, extension);
             break;
    case 3:  l_fname = g_strdup_printf("%s%03ld%s", basename, nr, extension);
             break;
    case 2:  l_fname = g_strdup_printf("%s%02ld%s", basename, nr, extension);
             break;
    default: l_fname = g_strdup_printf("%s%ld%s", basename, nr, extension);
             break;
  }
  return(l_fname);
}
