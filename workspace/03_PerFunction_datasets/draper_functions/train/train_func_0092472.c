update(mailsession * session)
{
  int r;
  struct feed_session_state_data * data;
  time_t value;

  data = get_data(session);

  value = time(NULL);
  if (data->feed_last_update != (time_t) -1) {
    if (value - data->feed_last_update < MIN_DELAY)
      return;
  }

  r = newsfeed_update(data->feed_session, -1);
  data->feed_error = feeddriver_feed_error_to_mail_error(r);
  if (data->feed_error == MAIL_NO_ERROR) {
    value = time(NULL);
    data->feed_last_update = value;
  }
}
