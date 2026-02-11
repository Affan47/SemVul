agvViewTransform(void)
{
  switch (MoveMode) {
    case FLYING:
      FlyLookFrom(Ex, Ey, Ez, EyeAz, EyeEl);
      break;
    case POLAR:
      PolarLookFrom(EyeDist, EyeEl, EyeAz);
      break;
    }
}
