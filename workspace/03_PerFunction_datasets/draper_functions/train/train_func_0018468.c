parameters(mailsession * session,
    int id, void * value)
{
  struct maildir_cached_session_state_data * data;
  int r;

  data = get_cached_data(session);

  switch (id) {
  case MAILDIRDRIVER_CACHED_SET_CACHE_DIRECTORY:
    strncpy(data->md_cache_directory, value, PATH_MAX);
    data->md_cache_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(data->md_cache_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  case MAILDIRDRIVER_CACHED_SET_FLAGS_DIRECTORY:
    strncpy(data->md_flags_directory, value, PATH_MAX);
    data->md_flags_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(data->md_flags_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  default:
    return mailsession_parameters(data->md_ancestor, id, value);
  }
}
