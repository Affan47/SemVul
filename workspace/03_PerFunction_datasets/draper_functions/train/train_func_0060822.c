get_time(MYSQL_TIME *ltime)
{
  char buff[40];
  String tmp(buff,sizeof(buff),&my_charset_bin),*res;
  if (!(res=val_str(&tmp)) ||
      str_to_time_with_warn(res->charset(), res->ptr(), res->length(), ltime))
    return 1;
  return 0;
}
