check_unzip (const char *pw)
{
  char buff[1024];
  char path[1024];
  char escpw[256];
  int status;

  escape_pw (escpw, pw);
  path_for_shell (path, file_path[0]);

  sprintf (buff, "unzip -qqtP \"%s\" %s " DEVNULL, escpw, path);

  status = system (buff);

#undef REDIR

  if (status == EXIT_SUCCESS)
    {
      printf("\n\nPASSWORD FOUND!!!!: pw == %s\n", pw);
      exit (EXIT_SUCCESS);
    }

  return !status;
}
