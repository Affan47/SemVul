gnc_localtime (const time64 *secs)
{
     struct tm *time = g_slice_alloc0 (sizeof (struct tm));
     if (gnc_localtime_r (secs, time) == NULL)
     {
	  gnc_tm_free (time);
	  return NULL;
     }
     return time;
}
