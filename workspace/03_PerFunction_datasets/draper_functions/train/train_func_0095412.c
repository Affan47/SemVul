ConstrainEl(void)
{
  if (EyeEl <= -90) {
    EyeEl = -89.99;
    return 1;
  } else if (EyeEl >= 90) {
    EyeEl = 89.99;
    return 1;
  }
  return 0;
}
