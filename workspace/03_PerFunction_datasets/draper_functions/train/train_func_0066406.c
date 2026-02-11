fix_ut_type_field(struct utmp *rec)
{
  int mods = 0;


  if (rec->ut_line[0] == OLD_TIME_CHAR)
    mods = 1, rec->ut_type = OLD_TIME;
  else if (rec->ut_line[0] == NEW_TIME_CHAR)
    mods = 1, rec->ut_type = NEW_TIME;
  else if (rec->ut_line[0] == BOOT_TIME_CHAR)
    {
      if ((strncmp (rec->ut_name, "reboot", NAME_LEN) == 0)
          && (rec->ut_type != BOOT_TIME))
        mods = 1, rec->ut_type = BOOT_TIME;
#ifdef RUN_LVL
      else if ((strncmp (rec->ut_name, "shutdown", NAME_LEN) == 0)
               && (rec->ut_type != RUN_LVL))
        mods = 1, rec->ut_type = RUN_LVL;
#else


      else if ((strncmp (rec->ut_name, "shutdown", NAME_LEN) == 0)
               && (rec->ut_type != BOOT_TIME))
        mods = 1, rec->ut_type = BOOT_TIME;
#endif
    }


#ifdef RUN_LVL
  if ((rec->ut_type == RUN_LVL)
      && (strncmp (rec->ut_name, "reboot", NAME_LEN) == 0)
      && (rec->ut_type != BOOT_TIME))
    mods = 1, rec->ut_type = BOOT_TIME;

  if ((rec->ut_type == BOOT_TIME)
      && (strncmp (rec->ut_name, "shutdown", NAME_LEN) == 0)
      && (rec->ut_type != RUN_LVL))
    mods = 1, rec->ut_type = RUN_LVL;
#endif

#if defined (USER_PROCESS) && defined (DEAD_PROCESS)
  if ((rec->ut_type == USER_PROCESS)
      && (rec->ut_name[0] == '\0'))
    mods = 1, rec->ut_type = DEAD_PROCESS;
#endif


#if defined (USER_PROCESS) && defined (DEAD_PROCESS)
  if ((rec->ut_type < 1) || (rec->ut_type > UTMAXTYPE))
    {
      if (rec->ut_line[0] != '\0')
        {
          if (rec->ut_name[0] != '\0')
            mods = 1, rec->ut_type = USER_PROCESS;
          else
            mods = 1, rec->ut_type = DEAD_PROCESS;
        }
    }
#endif

  return mods;
}
