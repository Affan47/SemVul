newsnntp_date(newsnntp * f, struct tm * tm)
{
  char command[NNTP_STRING_SIZE];
  int r;
  char * response;
  char year[5];
  char month[3];
  char day[3];
  char hour[3];
  char minute[3];
  char second[3];

  snprintf(command, NNTP_STRING_SIZE, "DATE\r\n");
  r = send_command(f, command);
  if (r == -1)
    return NEWSNNTP_ERROR_STREAM;

  response = read_line(f);
  if (response == NULL)
    return NEWSNNTP_ERROR_STREAM;

  r = parse_response(f, response);

  switch (r) {
  case 111:
    strfcpy(year, f->nntp_response, 4);
    strfcpy(month, f->nntp_response + 4, 2);
    strfcpy(day, f->nntp_response + 6, 2);
    strfcpy(hour, f->nntp_response + 8, 2);
    strfcpy(minute, f->nntp_response + 10, 2);
    strfcpy(second, f->nntp_response + 12, 2);

    tm->tm_year = atoi(year);
    tm->tm_mon = atoi(month);
    tm->tm_mday = atoi(day);
    tm->tm_hour = atoi(hour);
    tm->tm_min = atoi(minute);
    tm->tm_sec = atoi(second);

    return NEWSNNTP_NO_ERROR;

  default:
    return NEWSNNTP_ERROR_UNEXPECTED_RESPONSE;
  }
}
