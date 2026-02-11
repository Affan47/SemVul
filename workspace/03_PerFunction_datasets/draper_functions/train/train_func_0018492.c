value2human (double bytes, double time, double *data, double *speed,
             char *metric)
{
  if (bytes > 1000 && bytes < 1000 * 1000)
    {
      *data = ((double) bytes) / 1000;
      *speed = *data / time;
      strcpy (metric, "Kb");
      return;
    }
  else if (bytes >= 1000 * 1000 && bytes < 1000 * 1000 * 1000)
    {
      *data = ((double) bytes) / (1000 * 1000);
      *speed = *data / time;
      strcpy (metric, "Mb");
      return;
    }
  else if (bytes >= 1000 * 1000 * 1000)
    {
      *data = ((double) bytes) / (1000 * 1000 * 1000);
      *speed = *data / time;
      strcpy (metric, "Gb");
      return;
    }
  else
    {
      *data = (double) bytes;
      *speed = *data / time;
      strcpy (metric, "bytes");
      return;
    }
}
