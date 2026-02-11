caml_extunix_asctime(value v_t)
{
  struct tm tm;
  char buf[32];

  fill_tm(&tm, v_t);
  if (NULL == asctime_r(&tm,buf))
    unix_error(EINVAL, "asctime", Nothing);
  return caml_copy_string(buf);
}
