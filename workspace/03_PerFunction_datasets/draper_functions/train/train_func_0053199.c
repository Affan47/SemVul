agvMove(void)
{
  switch (MoveMode)  {
    case FLYING:
      Ex += EyeMove*sin(TORAD(EyeAz))*cos(TORAD(EyeEl));
      Ey += EyeMove*sin(TORAD(EyeEl));
      Ez -= EyeMove*cos(TORAD(EyeAz))*cos(TORAD(EyeEl));
      break;

    case POLAR:
      EyeEl += ElSpin;
      EyeAz += AzSpin;
      if (ConstrainEl()) {
        ElSpin = -ElSpin;

        if (fabs(ElSpin) > fabs(AzSpin))
          AzSpin = fabs(ElSpin) * ((AzSpin > 0) ? 1 : -1);
      }
      break;
    }

  if (AdjustingAzEl) {
    dAz *= SLOW_DAZ;
    dEl *= SLOW_DEL;
  }

  if (AllowIdle) {
    glutSetWindow(RedisplayWindow);
    glutPostRedisplay();
  }
}
