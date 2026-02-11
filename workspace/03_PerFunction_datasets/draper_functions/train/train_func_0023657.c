get_confirmed_pass (bool empty_ok)
{
  if (batch)
    return cfg.password;
  else
    {
      const char *pass = NULL;
      char *copy = NULL;

      do
        {
          if (pass)
            printf ("Password missmatch, try again.\n");

          free (copy);

          pass = getpass ("Enter password: ");
          copy = strdup (pass);
          pass = getpass ("Confirm password: ");
        }
      while (strcmp (pass, copy) != 0 && !(empty_ok && *pass == '\0'));

      free (copy);

      return pass;
    }
}
