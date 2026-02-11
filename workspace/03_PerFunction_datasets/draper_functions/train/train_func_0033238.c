fsysdep_terminal_restore ()
{
  if (! fSterm)
    return TRUE;

  if (! fsetterminfo (0, &sSterm_orig))
    {
      ulog (LOG_ERROR, "Can't restore terminal: %s", strerror (errno));
      return FALSE;
    }
  return TRUE;
}
