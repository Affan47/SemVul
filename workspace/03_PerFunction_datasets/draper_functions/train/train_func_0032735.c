sunlight()
{
 calendar sunrise_time = sunrise(), sunset_time = sunset();

 int mins = 0, sunrise_mins = 0, sunset_mins = 0;
 mins = minutes_past_midnight();
 sunrise_mins = sunrise_time.minutes_past_midnight();
 sunset_mins = sunset_time.minutes_past_midnight();

 int moonlight = 1 + int(moon()) * MOONLIGHT_LEVEL;

 if (mins > sunset_mins + TWILIGHT_MINUTES || mins < sunrise_mins)
  return moonlight;

 else if (mins >= sunrise_mins && mins <= sunrise_mins + TWILIGHT_MINUTES) {

  double percent = double(mins - sunrise_mins) / TWILIGHT_MINUTES;
  return int( double(moonlight)      * (1. - percent) +
              double(DAYLIGHT_LEVEL) * percent         );

 } else if (mins >= sunset_mins && mins <= sunset_mins + TWILIGHT_MINUTES) {

  double percent = double(mins - sunset_mins) / TWILIGHT_MINUTES;
  return int( double(DAYLIGHT_LEVEL) * (1. - percent) +
              double(moonlight)      * percent         );

 } else
  return DAYLIGHT_LEVEL;
}
