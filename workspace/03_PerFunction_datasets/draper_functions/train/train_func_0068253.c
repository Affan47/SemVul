usecs_to_str (unsigned long long usec)
{
   char *size = (char *) xmalloc (sizeof (char) * 11);
   if (usec >= HOUR)
      snprintf (size, 11, "%.2f hr", (double) (usec) / HOUR);
   else if (usec >= MINS)
      snprintf (size, 11, "%.2f mn", (double) (usec) / MINS);
   else if (usec >= SECS)
      snprintf (size, 11, "%.2f  s", (double) (usec) / SECS);
   else if (usec >= MILS)
      snprintf (size, 11, "%.2f ms", (double) (usec) / MILS);
   else
      snprintf (size, 11, "%.2f us", (double) (usec));

   return size;
}
