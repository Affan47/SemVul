int_to_timestring (int int_time, char *string_time, gint length)
{
  int sign = int_time < 0;
  int_time = abs (int_time);
  if (int_time % 1000)
    snprintf (string_time, length, "%s%02d:%02d:%06.3lf",
	      sign ? "-" : "",
	      int_time / 3600000,
	      (int_time / 60000) % 60,
	      (int_time % 60000) / 1000.0);
  else
    snprintf (string_time, length, "%s%02d:%02d:%02.0lf",
	      sign ? "-" : "",
	      int_time / 3600000,
	      (int_time / 60000) % 60,
	      (int_time % 60000) / 1000.0);
}
