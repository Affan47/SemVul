ho_recognize_font_1_resh (const double *array_in)
{
  double return_value = 0.0;

  if (TOP_HBAR)
    return_value += 0.1;
  if (RIGHT_VBAR)
    return_value += 0.1;
  if (!BOTTOM_HBAR)
    return_value += 0.1;
  if (!LEFT_VBAR)
    return_value += 0.1;
  if (!TOP_RIGTH_EDGE)
    return_value += 0.1;
  if (RIGHT_BOTTOM_EDGE)
    return_value += 0.1;

  if (BOTTOM_HBAR)
    return_value -= 0.3;
  if (MID_BOTTOM_NOTCH || RIGHT_BOTTOM_NOTCH)
    return_value -= 0.2;
  if (LEFT_VBAR)
    return_value -= 0.3;
  if (MID_VBAR)
    return_value -= 0.1;
  if (HEY_PART)
    return_value -= 0.3;
  if (BOTTOM > 0.60)
    return_value -= 0.3;
  if (BOTTOM < 0.45)
    return_value -= 0.3;
  if (TOP_RIGTH_EDGE)
    return_value -= 0.1;
  if (WIDTH < 0.3)
    return_value -= 0.3;
  if (WIDTH_BY_HEIGHT < 0.6)
    return_value -= 0.3;
  if (TWO_VLINES_DOWN)
    return_value -= 0.3;
  if (BOTTOM_LEFT < 0.9)
    return_value -= 0.3;
  if (MID_LEFT < 0.9)
    return_value -= 0.3;
  if (WIDTH < 0.35 || HEIGHT < 0.35)
    return_value -= 0.2;
  if (WIDTH < 0.25)
    return_value -= 0.2;

  return return_value;
}
