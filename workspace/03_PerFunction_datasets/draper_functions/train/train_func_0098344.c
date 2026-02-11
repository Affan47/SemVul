DetermineNextDayStop()
{
  struct tm* lctime;
  time_t current_time = time(0);
  lctime = gmtime(&current_time);
  int gm_hour = lctime->tm_hour;
  time_t gm_time = mktime(lctime);
  lctime = localtime(&current_time);
  int local_hour = lctime->tm_hour;

  int tzone_offset = local_hour - gm_hour;
  if(gm_time > current_time && gm_hour < local_hour)
    {

    tzone_offset -= 24;
    }
  else if(gm_time < current_time && gm_hour > local_hour)
    {

    tzone_offset += 24;
    }

  tzone_offset *= 100;
  char buf[1024];
  sprintf(buf, "%d%02d%02d %s %+05i",
          lctime->tm_year + 1900,
          lctime->tm_mon + 1,
          lctime->tm_mday,
          this->StopTime.c_str(),
          tzone_offset);

  time_t stop_time = curl_getdate(buf, &current_time);

  if(stop_time < current_time)
    {
    this->NextDayStopTime = true;
    }
}
