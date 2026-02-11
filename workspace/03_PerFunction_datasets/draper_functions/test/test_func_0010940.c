cmd_new(void)
{
  InitVars ();
  NewPosition ();

  if (!(flags & ANALYZE))
    CLEAR (flags, MANUAL);
  CLEAR (flags, THINK);
  myrating = opprating = 0;
  SetDataToEngine( token[0] );
}
