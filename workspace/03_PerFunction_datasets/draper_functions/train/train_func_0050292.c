detect_telnet_flood(char *floodhost)
{
  struct flag_record fr = { FR_GLOBAL | FR_CHAN | FR_ANYWH, 0, 0, 0, 0, 0 };

  get_user_flagrec(get_user_by_host(floodhost), &fr, NULL);
  if (!flood_telnet_thr || (glob_friend(fr) && !par_telnet_flood))
    return 0;
  if (egg_strcasecmp(lasttelnethost, floodhost)) {
    strcpy(lasttelnethost, floodhost);
    lasttelnettime = now;
    lasttelnets = 0;
    return 0;
  }
  if (lasttelnettime < now - flood_telnet_time) {

    lasttelnettime = now;
    lasttelnets = 0;
    return 0;
  }
  lasttelnets++;
  if (lasttelnets >= flood_telnet_thr) {

    lasttelnets = 0;
    lasttelnettime = 0;
    lasttelnethost[0] = 0;
    putlog(LOG_MISC, "*", IRC_TELNETFLOOD, floodhost);
    addignore(floodhost, origbotname, "Telnet connection flood",
              now + (60 * ignore_time));
    return 1;
  }
  return 0;
}
