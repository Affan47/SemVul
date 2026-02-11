get_date_time_format_str(KNOWN_DATE_TIME_FORMAT *format,
				     timestamp_type type)
{
  switch (type) {
  case MYSQL_TIMESTAMP_DATE:
    return format->date_format;
  case MYSQL_TIMESTAMP_DATETIME:
    return format->datetime_format;
  case MYSQL_TIMESTAMP_TIME:
    return format->time_format;
  default:
    DBUG_ASSERT(0);
    return 0;
  }
}
