GNATS_ftyp (int ac, char **av)
{
  int x;

  if (ac < 1)
    {

      chk_nargs (ac, "field name");
      return;
    }
  for (x = 0; x < ac; x++)
    {
      char contchar =  (x < (ac - 1)) ? '-' : ' ';
      FieldIndex fnum = find_field_index (currentDatabase, av[x]);

      if (fnum != InvalidFieldIndex)
	{
	  printf ("%d%c%s\n", CODE_INFORMATION, contchar,
		  fieldTypeAsString (fieldDefForIndex (fnum)->datatype));
	}
      else
	{
	  printf ("%d%cNo such field as `%s'\r\n",
		  CODE_INVALID_FIELD_NAME, contchar, av[x]);
	}
    }
}
