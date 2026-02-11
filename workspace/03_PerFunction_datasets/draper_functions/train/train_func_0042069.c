MoveOn(int v)
{
  if (v && ((MoveMode == FLYING && EyeMove != 0) ||
             (MoveMode == POLAR &&
             (AzSpin != 0 || ElSpin != 0 || AdjustingAzEl)))) {
    agvMoving = 1;
    if (AllowIdle)
      glutIdleFunc(agvMove);
  } else {
    agvMoving = 0;
    if (AllowIdle)
      glutIdleFunc(NULL);
  }
}
