tmcomp(struct tm * atmp, struct tm * btmp)
{
  register int	result;

  if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
      (result = (atmp->tm_mon - btmp->tm_mon)) == 0 &&
      (result = (atmp->tm_mday - btmp->tm_mday)) == 0 &&
      (result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
      (result = (atmp->tm_min - btmp->tm_min)) == 0)
    result = atmp->tm_sec - btmp->tm_sec;
  return result;
}
