sync_time(time_t arg_gpstime, char * arg_videotime)
{
  static time_t videotime_t;
  static struct tm * ptm_video;
  static time_t result;

  videotime_t = 0;
  ptm_video = gmtime(&videotime_t);
  if (arg_videotime) {
    sscanf(arg_videotime, "%2d%2d%2d", &ptm_video->tm_hour, &ptm_video->tm_min, &ptm_video->tm_sec);
  }
  videotime_t = mkgmtime(ptm_video);
  result = (arg_gpstime - videotime_t);
  return result;
}
