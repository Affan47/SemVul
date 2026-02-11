check_env(void) {
  if (getenv(AWAY_RCFILE)) {
    rcfile = getenv(AWAY_RCFILE);
    RCFILE_OP = 1;
    unsetenv(AWAY_RCFILE);
  }

  if (getenv(AWAY_NOTIME)) {
    TIME_OP = 1;
    unsetenv(AWAY_NOTIME);
  } else if (getenv(AWAY_TIME)) {
    if (atoi(getenv(AWAY_TIME)) >= MIN_TIME) {
      TIME = atoi(getenv(AWAY_TIME));
      TIME_OP = 1;
    }
    unsetenv(AWAY_TIME);
  }

  if (getenv(AWAY_PERSIST)) {
    PERSIST = atoi(getenv(AWAY_PERSIST));
    PERSIST_OP = 1;
    unsetenv(AWAY_PERSIST);
  }

  if (getenv(AWAY_MAIL)) {
    CHECK_MAIL = atoi(getenv(AWAY_MAIL));
    MAIL_OP = 1;
    unsetenv(AWAY_MAIL);
  }
}
