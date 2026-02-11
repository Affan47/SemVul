setFvwmUserDir(void)
{
  char *home_dir;

  if (FvwmUserDir != NULL)
    return;


  home_dir = getenv("HOME");
#ifdef HAVE_GETPWUID
  if (home_dir == NULL) {
    struct passwd* pw = getpwuid(getuid());
    if (pw != NULL)
      home_dir = safestrdup(pw->pw_dir);
  }
#endif
  if (home_dir == NULL)
    home_dir = "/";


  FvwmUserDir = getenv("FVWM_USERDIR");
  if (FvwmUserDir == NULL)
  {
    FvwmUserDir = safestrdup(CatString2(home_dir, "/.fvwm"));
  }
}
