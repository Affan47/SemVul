parse_rc (char *dir, char *file)
{
  FILE *rc;
  char *rc_file, buf[1024], *lvalue, *rvalue;

#ifdef DEBUG
  printf ("parse_rc\n");
#endif

  if ((rc_file = malloc (strlen (dir) + strlen (file) + 2)) == NULL)
    return;

  sprintf (rc_file, "%s/%s", dir, file);

  if ((rc = fopen (rc_file, "r")))
    {
      while (fgets (buf, sizeof buf, rc))
	{
	  lvalue = strtok (buf, "=");
	  if (lvalue)
	    {
	      if (!strcmp (lvalue, "key"))
		{
		  rvalue = strtok (NULL, "\n");
		  if (rvalue)
		    create_new_key (rvalue);
		}
	    }
	}
      fclose (rc);
    }
  else
    {
      printf ("Could not open the configuration.\n\n");
      usage ();
      exit (1);
    }
  free (rc_file);
  do_update = 0;
}
