cbf_set_current_timestamp (cbf_handle handle, unsigned int reserved,
                                                  int timezone)
{
  time_t timer;

  if (reserved != 0)

    return CBF_ARGUMENT;

  timer = time (NULL);

  if (timezone != CBF_NOTIMEZONE)

    timer += timezone * 60;

  cbf_failnez (cbf_set_timestamp (handle, reserved, timer, timezone, 1))

  return 0;
}
