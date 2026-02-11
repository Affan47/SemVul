range_as_text (const GstRTSPRange * range)
{
  if (range->min < 0)
    return NULL;
  else if (range->max < 0)
    return g_strdup_printf ("%d", range->min);
  else
    return g_strdup_printf ("%d-%d", range->min, range->max);
}
