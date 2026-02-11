display_ignore(int idx, int number, struct igrec *ignore)
{
  char dates[81], s[41];

  if (ignore->added) {
    daysago(now, ignore->added, s);
    sprintf(dates, "Started %s", s);
  } else
    dates[0] = 0;
  if (ignore->flags & IGREC_PERM)
    strcpy(s, "(perm)");
  else {
    char s1[41];

    days(ignore->expire, now, s1);
    sprintf(s, "(expires %s)", s1);
  }
  if (number >= 0)
    dprintf(idx, "  [%3d] %s %s\n", number, ignore->igmask, s);
  else
    dprintf(idx, "IGNORE: %s %s\n", ignore->igmask, s);
  if (ignore->msg && ignore->msg[0])
    dprintf(idx, "        %s: %s\n", ignore->user, ignore->msg);
  else
    dprintf(idx, "        %s %s\n", MODES_PLACEDBY, ignore->user);
  if (dates[0])
    dprintf(idx, "        %s\n", dates);
}
