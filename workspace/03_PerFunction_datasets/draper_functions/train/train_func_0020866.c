_hd_lookup_home_dir(HomeDir *home, const char *user)
{
  const char *home_dir;


  int login_user = !user || *user=='\0';


  if(!home) {
    errno = EINVAL;
    return NULL;
  };


  if(!login_user && strcmp(user, "+") == 0) {
    home_dir = hd_getpwd(home);
    if(!home_dir) {
      _err_record_msg(home->err, "Can't determine current directory",
		      END_ERR_MSG);
      return NULL;
    }
    return home_dir;
  };


  if(login_user) {
    home_dir = getenv("HOME");
    if(home_dir)
      return home_dir;
  };


#ifdef THREAD_COMPATIBLE
  {
    struct passwd *ret;
    int status;


    if(login_user)
      status = getpwuid_r(geteuid(), &home->pwd, home->buffer, home->buflen,
			  &ret);
    else
      status = getpwnam_r(user, &home->pwd, home->buffer, home->buflen, &ret);
    if(status || !ret) {
      _err_record_msg(home->err, "User '", user, "' doesn't exist.",
		      END_ERR_MSG);
      return NULL;
    };


    home_dir = home->pwd.pw_dir;
  };


#else
  {
    struct passwd *pwd = login_user ? getpwuid(geteuid()) : getpwnam(user);
    if(!pwd) {
      _err_record_msg(home->err, "User '", user, "' doesn't exist.",
		      END_ERR_MSG);
      return NULL;
    };


    home_dir = pwd->pw_dir;
  };
#endif
  return home_dir;
}
