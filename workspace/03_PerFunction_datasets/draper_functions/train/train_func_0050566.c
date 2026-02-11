user_username(char *buf, size_t bufsz)
{


  {
    char *env = getenv("USER");

    if (env) {
      fc_strlcpy(buf, env, bufsz);
      if (is_ascii_name(buf)) {
        log_verbose("USER username is %s", buf);
        return buf;
      }
    }
  }

#ifdef HAVE_GETPWUID


  {
    struct passwd *pwent = getpwuid(getuid());

    if (pwent) {
      fc_strlcpy(buf, pwent->pw_name, bufsz);
      if (is_ascii_name(buf)) {
        log_verbose("getpwuid username is %s", buf);
        return buf;
      }
    }
  }
#endif

#ifdef WIN32_NATIVE

  {
    char name[UNLEN + 1];
    DWORD length = sizeof(name);

    if (GetUserName(name, &length)) {
      fc_strlcpy(buf, name, bufsz);
      if (is_ascii_name(buf)) {
        log_verbose("GetUserName username is %s", buf);
        return buf;
      }
    }
  }
#endif

#ifdef ALWAYS_ROOT
  fc_strlcpy(buf, "name", bufsz);
#else
  fc_snprintf(buf, bufsz, "name%d", (int) getuid());
#endif
  log_verbose("fake username is %s", buf);
  fc_assert(is_ascii_name(buf));
  return buf;
}
