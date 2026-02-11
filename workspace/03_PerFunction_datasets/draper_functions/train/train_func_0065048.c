gnobots_statusbar_set (gint score,
		       gint level, gint stel, gint rem1, gint rem2)
{
  if (statusbar == NULL)
    return FALSE;

  gnobots_statusbar_set_score (score);
  gnobots_statusbar_set_level (level);
  gnobots_statusbar_set_safe_teleports (stel);
  gnobots_statusbar_set_remaining (rem1, rem2);

  return TRUE;
}
