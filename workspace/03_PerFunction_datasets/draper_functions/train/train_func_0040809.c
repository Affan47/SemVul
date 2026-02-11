GNATS_dbls (int ac, char **av ATTRIBUTE_UNUSED)
{
  AdmEntry *dbl;
  ErrorDesc err;

  if (ac != 0)
    {
      noargs ("DBLS");
      return;
    }

  dbl = getDatabaseList (&err);
  if (dbl == NULL)
    {
      print_server_errors (err);
    }
  else
    {
      printf ("%d List follows.\r\n", CODE_TEXT_READY);
      while (dbl != NULL)
	{
	  printf ("%s\r\n", dbl->admFields[DatabaseListKey]);
	  dbl = dbl->next;
	}
      printf (".\r\n");
    }
}
