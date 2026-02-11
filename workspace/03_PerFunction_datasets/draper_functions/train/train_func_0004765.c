get_ver_flags (unsigned int flags)
{
  static char buff[32];

  buff[0] = 0;

  if (flags == 0)
    return _("none");

  if (flags & VER_FLG_BASE)
    strcat (buff, "BASE ");

  if (flags & VER_FLG_WEAK)
    {
      if (flags & VER_FLG_BASE)
	strcat (buff, "| ");

      strcat (buff, "WEAK ");
    }

  if (flags & VER_FLG_INFO)
    {
      if (flags & (VER_FLG_BASE|VER_FLG_WEAK))
	strcat (buff, "| ");

      strcat (buff, "INFO ");
    }

  if (flags & ~(VER_FLG_BASE | VER_FLG_WEAK | VER_FLG_INFO))
    strcat (buff, _("| <unknown>"));

  return buff;
}
