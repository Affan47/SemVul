isRightBreakBeamTriggered(void) const
{
  if (myParams->haveTableSensingIR())
  {
    if (myParams->haveNewTableSensingIR() && myIODigInSize > 3)
      return !(getIODigIn(3) & ArUtil::BIT3);
    else
      return !(getDigIn() & ArUtil::BIT2);
  }
  return 0;
}
