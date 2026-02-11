normalize_date (EggDateTime *edt)
{
   GDate date, min_date, max_date;

   if (edt->priv->lazy)
      return;

   g_date_clear (&date, 1);
   g_date_set_dmy (&date, edt->priv->day, edt->priv->month, edt->priv->year);
   g_date_clear (&min_date, 1);
   g_date_set_dmy (&min_date, edt->priv->clamp_minday, edt->priv->clamp_minmonth, edt->priv->clamp_minyear);
   g_date_clear (&max_date, 1);
   g_date_set_dmy (&max_date, edt->priv->clamp_maxday, edt->priv->clamp_maxmonth, edt->priv->clamp_maxyear);

   g_date_clamp (&date, &min_date, &max_date);

   edt->priv->year  = date.year;
   edt->priv->month = date.month;
   edt->priv->day   = date.day;
   edt->priv->date_valid = TRUE;
}
