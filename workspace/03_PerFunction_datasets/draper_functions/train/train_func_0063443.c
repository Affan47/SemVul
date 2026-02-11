icmpsub_check_sending_rate(void)
{
  static int count = 0;
  static time_t from;
  time_t now = time(NULL);

  if (now - from > 1) {

    count = 0;
    from = now;
  }

  if (count > ICMPSUB_RATE_LIMIT_COUNT) {

    return (-1);
  }

  count = count + 1;

  return (0);
}
