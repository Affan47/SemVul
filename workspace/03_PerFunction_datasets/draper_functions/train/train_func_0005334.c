panel_hidden(const PANEL * pan)
{
  T((T_CALLED("panel_hidden(%p)"), pan));
  if (!pan)
    returnCode(ERR);
  returnCode(IS_LINKED(pan) ? FALSE : TRUE);
}
