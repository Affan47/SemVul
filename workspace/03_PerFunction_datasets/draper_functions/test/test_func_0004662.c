setTimeZone(bool negativeTimeZone, unsigned long timeZone)
{
  setSemiOctetsInteger(timeZone / 15, 2);
  if (!negativeTimeZone)
    *(_op - 1) |= 8;
}
