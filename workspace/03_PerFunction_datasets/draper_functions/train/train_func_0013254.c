nntpdriver_cached_parameters(mailsession * session,
					int id, void * value)
{
  struct nntp_cached_session_state_data * cached_data;
  int r;

  cached_data = get_cached_data(session);

  switch (id) {
  case NNTPDRIVER_CACHED_SET_CACHE_DIRECTORY:
    strncpy(cached_data->nntp_cache_directory, value, PATH_MAX);
    cached_data->nntp_cache_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(cached_data->nntp_cache_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  case NNTPDRIVER_CACHED_SET_FLAGS_DIRECTORY:
    strncpy(cached_data->nntp_flags_directory, value, PATH_MAX);
    cached_data->nntp_flags_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(cached_data->nntp_flags_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  default:
    return mailsession_parameters(get_ancestor(session), id, value);
  }
}
