calculate_medium_pression (GSList *list)
{
  guint i = 0;
  gdouble total_pressure = 0;
  guint lenght = g_slist_length (list);

  for (i=0; i<lenght; i++)
    {
      AnnotatePoint *cur_point = (AnnotatePoint *) g_slist_nth_data (list, i);
      total_pressure = total_pressure + cur_point->pressure;
    }

  return total_pressure/i;
}
