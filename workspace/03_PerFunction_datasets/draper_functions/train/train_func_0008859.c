mboxdriver_cached_parameters(mailsession * session,
					int id, void * value)
{
  struct mbox_cached_session_state_data * data;
  int r;

  data = get_cached_data(session);

  switch (id) {
  case MBOXDRIVER_CACHED_SET_CACHE_DIRECTORY:
    strncpy(data->mbox_cache_directory, value, PATH_MAX);
    data->mbox_cache_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(data->mbox_cache_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  case MBOXDRIVER_CACHED_SET_FLAGS_DIRECTORY:
    strncpy(data->mbox_flags_directory, value, PATH_MAX);
    data->mbox_flags_directory[PATH_MAX - 1] = '\0';

    r = generic_cache_create_dir(data->mbox_flags_directory);
    if (r != MAIL_NO_ERROR)
      return r;

    return MAIL_NO_ERROR;

  case MBOXDRIVER_SET_NO_UID:
    return MAIL_ERROR_INVAL;

  default:
    return mailsession_parameters(data->mbox_ancestor, id, value);
  }
}
