split_entry (const char *entry, char **name, size_t *name_len,
             char **description, size_t *description_len)
{
  char *endptr;


  char *ptr = strchr (entry, '.');
  while (ptr && ptr[1] != ' ' && ptr[1] != '\t' && ptr[1] != '\n') {
    ptr = strchr (ptr + 1, '.');
  }


  if (!ptr)
    {
      size_t length = strlen (entry);
      if (length == 0)
        return;
      *name = strdup (entry);
      *name_len = length + 1;
      return;
    }


  *name_len = (size_t) (ptr - entry + 1);
  *name = xmalloc (*name_len + 1);
  (*name)[0] = '\0';
  strncat (*name, entry, *name_len);

  ptr++;
  *description = xmalloc (strlen (entry));
  (*description)[0] = '\0';

  while (ptr[0] != '\0')
    {

      while (isspace(ptr[0]))
        ptr++;


      if (ptr[0] == '\0')
        continue;


      endptr = strchr (ptr, '\n');

      if (endptr)
        {
          size_t length  = (size_t) (endptr - ptr) / sizeof (char);
          strncat (*description, ptr, length);
          ptr = endptr;


          ptr++;
          if (length > 1 && strlen (ptr) > 0)
            {
              endptr--;

              if (*endptr == '.')
                strncat (*description, "  ", 2);
              else if (!isspace (*endptr))
                strncat (*description, " ", 1);
            }
        }

      else
        {

          size_t length = strlen (ptr);
          strncat (*description, ptr, length);
          ptr += length;
        }
    }

  strncat (*description, "\n", 1);
  *description_len = strlen (*description);
}
