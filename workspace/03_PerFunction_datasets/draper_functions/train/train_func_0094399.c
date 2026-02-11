create_allow(Rlink_user *user, CmdFlags *flags)
{
  char *pwd;
  Allow *allow;

  allow = ALLOC(Allow);
  allow->id = NULL;
  allow->expr = ds_init(NULL);
  init_grant_attrs(&allow->attrs);
  allow->next = NULL;

  if (user == NULL || (pwd = user->password) == NULL)
	pwd = flags->default_password;

  if (user != NULL)
	ds_asprintf(allow->expr, "user(\"%s\")\n", user->username);

  if (pwd != NULL) {
	char *str;
	Passwd_digest_alg alg;

	if (passwd_algname == NULL) {
	  if (passwd_get_digest_algorithm(&passwd_algname, &alg) == -1)
		return(NULL);
	}
	else {
	  alg = passwd_lookup_digest_algorithm(passwd_algname);
	  if (alg == PASSWD_ALG_NONE)
		return(NULL);
	}
	if ((str = passwd_make_digest(alg, pwd, NULL)) == NULL)
	  return(NULL);

	ds_asprintf(allow->expr,
				"    %s password(check, ${Args::PASSWORD}, \"%s\")\n",
				(user != NULL) ? "and" : "", str);
  }

  return(allow);
}
