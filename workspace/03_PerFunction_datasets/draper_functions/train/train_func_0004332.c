egg_datetime_set_from_gdate (EggDateTime *edt, GDate *date)
{
   g_return_if_fail (edt != NULL);
   g_return_if_fail (EGG_IS_DATETIME (edt));
   g_return_if_fail (date != NULL);

   if (g_date_valid (date))
      egg_datetime_set_date (edt, date->year, date->month, date->day);
   else
      egg_datetime_set_none (edt);
}
