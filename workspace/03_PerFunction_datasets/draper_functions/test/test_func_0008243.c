ho_recognize_font_1_het (const double *array_in)
{
  double return_value = 0.0;

  if (TOP_HBAR)
    return_value += 0.1;
  if (LEFT_VBAR)
    return_value += 0.1;
  if (RIGHT_VBAR)
    return_value += 0.1;
  if (!BOTTOM_HBAR)
    return_value += 0.1;
  if (BOTTOM_LEFT < (MID_LEFT + 0.1))
    return_value += 0.1;
  if (TWO_VLINES_DOWN)
    return_value += 0.1;

  if (!TOP_HBAR)
    return_value -= 0.1;
  if (!LEFT_VBAR)
    return_value -= 0.1;
  if (!RIGHT_VBAR)
    return_value -= 0.1;
  if (BOTTOM_HBAR)
    return_value -= 0.2;
  if (BOTTOM_LEFT_EDGE)
    return_value -= 0.2;
  if (BOTTOM_MID < 0.9)
    return_value -= 0.2;
  if (MID_TOP_NOTCH && TOP_MID > 0.2)
    return_value -= 0.3;
  if (BOTTOM_LEFT < (MID_LEFT + 0.1))
    return_value -= 0.1;
  if (!TWO_VLINES_DOWN)
    return_value -= 0.3;
  if (RIGHT_TOP_EDGE)
    return_value -= 0.2;
  if (HEY_PART)
    return_value -= 0.2;
  if (ONE_HOLE)
    return_value -= 0.3;
  if (TOP_LEFT > (BOTTOM_LEFT + 0.1))
    return_value -= 0.1;
  if (!BOTTOM_RIGHT_END)
    return_value -= 0.2;

  return return_value;
}
