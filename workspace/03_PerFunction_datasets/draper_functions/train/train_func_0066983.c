Button_Tiling_mode(void)
{
  if (Tiling_mode)
    Effect_function=No_effect;
  else
  {
    Effect_function=Effect_tiling;
    Shade_mode=0;
    Quick_shade_mode=0;
    Colorize_mode=0;
    Smooth_mode=0;
    Smear_mode=0;
  }
  Tiling_mode=!Tiling_mode;
}
