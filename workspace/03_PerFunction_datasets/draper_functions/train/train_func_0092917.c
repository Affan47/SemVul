print_line(
    ipp_attribute_t *attr,
    int             num_displayed,
    char            **displayed,
    size_t          *widths)
{
  int		i;
  size_t	maxlength;
  char		*buffer;
  ipp_attribute_t *current;


  for (i = 1, maxlength = widths[0]; i < num_displayed; i ++)
    if (widths[i] > maxlength)
      maxlength = widths[i];

  maxlength += 2;

  if ((buffer = malloc(maxlength)) == NULL)
    return;


  if (attr)
  {
    for (i = 0; i < num_displayed; i ++)
    {
      if (i)
        putchar(' ');

      buffer[0] = '\0';

      for (current = attr; current; current = current->next)
      {
        if (!current->name)
          break;
        else if (!strcmp(current->name, displayed[i]))
        {
          ippAttributeString(current, buffer, maxlength);
          break;
        }
      }

      printf("%*s", (int)-widths[i], buffer);
    }
    putchar('\n');
  }
  else
  {
    for (i = 0; i < num_displayed; i ++)
    {
      if (i)
        putchar(' ');

      printf("%*s", (int)-widths[i], displayed[i]);
    }
    putchar('\n');

    for (i = 0; i < num_displayed; i ++)
    {
      if (i)
	putchar(' ');

      memset(buffer, '-', widths[i]);
      buffer[widths[i]] = '\0';
      fputs(buffer, stdout);
    }
    putchar('\n');
  }

  free(buffer);
}
