process_auth(ETERM *pid, ETERM *data)
{
  int retval = 0;
  ETERM *pattern, *srv, *user, *pass;
  char *service, *username, *password;
  pattern = erl_format("{Srv, User, Pass}");
  if (erl_match(pattern, data))
    {
      srv = erl_var_content(pattern, "Srv");
      service = erl_iolist_to_string(srv);
      user = erl_var_content(pattern, "User");
      username = erl_iolist_to_string(user);
      pass = erl_var_content(pattern, "Pass");
      password = erl_iolist_to_string(pass);
      retval = process_reply(pid, CMD_AUTH, auth(service, username, password));
      erl_free_term(srv);
      erl_free_term(user);
      erl_free_term(pass);
      erl_free(service);
      erl_free(username);
      erl_free(password);
    };
  erl_free_term(pattern);
  return retval;
}
