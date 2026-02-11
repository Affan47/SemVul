xml_fnwrite_encode_entity(FILE *file, const char *str, int n)
{
  int i;


  for(i=0; i<n; i++)
  {
    switch(str[i])
    {
      case '<'  : fwrite("&lt;", 4, 1, file);
                  break;

      case '>'  : fwrite("&gt;", 4, 1, file);
                  break;

      case '&'  : fwrite("&amp;", 5, 1, file);
                  break;

      case '\'' : fwrite("&apos;", 6, 1, file);
                  break;

      case '\"' : fwrite("&quot;", 6, 1, file);
                  break;

      default   : fputc(str[i], file);
                  break;
    }
  }
}
