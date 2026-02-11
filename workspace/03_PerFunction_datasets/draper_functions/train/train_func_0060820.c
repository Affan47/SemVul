send_pwd_to_eterm ()
{
  char *pwd;

  pwd = get_string_value ("PWD");
  if (pwd == 0)
    pwd = get_working_directory ("eterm");
  fprintf (stderr, "\032/%s\n", pwd);
}
