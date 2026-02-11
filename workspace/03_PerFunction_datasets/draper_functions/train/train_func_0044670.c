dTimerNow (const char *description)
{
  if (num < MAXNUM) {

    getClockCount (event[num].cc);
    event[num].description = const_cast<char*> (description);
    num++;
  }
}
