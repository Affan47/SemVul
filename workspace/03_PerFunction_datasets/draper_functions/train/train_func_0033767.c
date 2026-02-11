store_time(MYSQL_TIME *tm)
{
#ifndef DBUG_OFF
  DBUG_ASSERT(field_types == 0 ||
	      field_types[field_pos] == MYSQL_TYPE_TIME);
  field_pos++;
#endif
  char buff[40];
  uint length;
  uint day= (tm->year || tm->month) ? 0 : tm->day;
  length= sprintf(buff, "%s%02ld:%02d:%02d", tm->neg ? "-" : "",
                  (long) day*24L+(long) tm->hour, (int) tm->minute,
                  (int) tm->second);
  if (tm->second_part)
    length+= sprintf(buff+length, ".%06d", (int) tm->second_part);
  return net_store_data((uchar*) buff, length);
}
