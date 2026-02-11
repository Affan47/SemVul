GNATS_fieldflags (int ac, char **av)
{
  int x;

  if (ac < 1)
    {
      printf ("%d At least one field name is required.\r\n", CODE_CMD_ERROR);
      return;
    }
  for (x = 0; x < ac; x++)
    {
      char contchar = ((x < (ac - 1)) ? '-' : ' ');
      FieldIndex fnum = find_field_index (currentDatabase, av[x]);

      if (fnum != InvalidFieldIndex)
	{
	  char *flags = getFieldFlags (fnum);

	  printf ("%d%c%s\r\n", CODE_INFORMATION, contchar, flags);
	  free (flags);
	}
      else
	{
	  printf ("%d%cNo such field as `%s'\r\n",
		  CODE_INVALID_FIELD_NAME, contchar, av[x]);
	}
    }
}
