cbf_set_timestamp (cbf_handle handle, unsigned int reserved,
                                          double       time,
                                          int          timezone,
                                          double       precision)
{
  int month, monthstep, year, day, hour, minute;

  double second, date;

  if (reserved != 0)

    return CBF_ARGUMENT;


  date = time / 86400.0 + 2440587.5;

  if (date < 1721060.5 || date > 5373484.5)

    return CBF_ARGUMENT;


  for (monthstep = 65536, month = 0; monthstep; monthstep >>= 1)
  {
    month += monthstep;

    if (cbf_gregorian_julian (month / 12,
                             (month % 12) + 1, 1, 0, 0, 0) > date)

     month -= monthstep;
  }


  year  =  month / 12;
  month = (month % 12) + 1;

  date -= cbf_gregorian_julian (year, month, 1, 0, 0, 0);

  day = (int) floor (date) + 1;

  date -= (day - 1);

  hour = (int) floor (date * 24.0);

  date -= hour / 24.0;

  minute = (int) floor (date * 1440.0);

  date -= minute / 1440.0;

  second = date * 86400.0;


  cbf_failnez (cbf_set_datestamp (handle, reserved, year, month, day,
                                     hour, minute, second,
                                     timezone, precision))

  return 0;
}
