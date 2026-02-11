get_version(void)
{
  if (the_tor_version == NULL) {
    if (strlen(tor_git_revision)) {
      tor_asprintf(&the_tor_version, "%s (git-%s)", VERSION, tor_git_revision);
    } else {
      the_tor_version = tor_strdup(VERSION);
    }
  }
  return the_tor_version;
}
