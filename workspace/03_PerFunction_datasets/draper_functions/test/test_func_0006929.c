stats_init(void)
{
  struct StatDesc *sd;


  for (statscount = 0, sd = statsinfo; sd->sd_name; sd++, statscount++) {}
  qsort(statsinfo, statscount, sizeof(statsinfo[0]), stats_cmp);


  for (sd = statsinfo; sd->sd_name; sd++)
  {
    if (!sd->sd_c)
      continue;
    else if (sd->sd_flags & STAT_FLAG_CASESENS)

      statsmap[sd->sd_c - CHAR_MIN] = sd;
    else
    {

      statsmap[ToLower(sd->sd_c) - CHAR_MIN] = sd;
      statsmap[ToUpper(sd->sd_c) - CHAR_MIN] = sd;
    }
  }
}
