ARTcontrol(ARTDATA *data, char *Control, CHANNEL *cp UNUSED)
{
  char *p, c;


  c = *Control;
  if ((c == 'c' || c == 'C') && strncasecmp(Control, "cancel", 6) == 0) {
    for (p = &Control[6]; ISWHITE(*p); p++)
      continue;
    if (*p && IsValidMessageID(p, true))
      ARTcancel(data, p, false);
    return;
  }
}
