normalize_month (gint month)
{
     month = (month % 12 + 12) % 12;
     return month == 0 ? 12 : month;
}
