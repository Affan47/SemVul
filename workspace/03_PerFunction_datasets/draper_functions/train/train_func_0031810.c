adjust_leap_second(MYSQL_TIME *t)
{
  if (t->second == 60 || t->second == 61)
    t->second= 59;
}
