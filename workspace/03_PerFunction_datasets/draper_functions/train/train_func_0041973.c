getNoBands(PS_RESOLUTION mode)
{
  if(mode>=6)
    return 0;

  if(mode>=3)
    mode = (PS_RESOLUTION)(mode-3);

  return psBands[mode];
}
