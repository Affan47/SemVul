GNATS_delete (int ac, char **av)
{
  if (chk_nargs (ac, "PR number"))
    {
      ErrorDesc err;
      int result = deletePR (currentDatabase, av[0], editEmailAddr, &err);

      if (result == 0)
	{
	  printf ("%d PR %s deleted.\r\n", CODE_OK, av[0]);
	}
      else
	{
	  print_server_errors (err);
	}
    }
}
