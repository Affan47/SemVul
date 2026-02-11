date_is_valid(GB_DATE_SERIAL *date)
{
  return ((date->month >= 1) && (date->month <= 12) &&
          (date->year >= DATE_YEAR_MIN) && (date->year <= DATE_YEAR_MAX) && (date->year != 0) &&
          (date->day >= 1) && (date->day <= days_in_months[date_is_leap_year(date->year)][(short)date->month]) &&
          (date->hour >= 0) && (date->hour <= 23) && (date->min >= 0) && (date->min <= 59) &&
          (date->sec >= 0) && (date->sec <= 59));
}
