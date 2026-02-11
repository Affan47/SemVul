ho_recognize_font_1_vav (const double *array_in)
{
  double return_value = 0.0;

  if (WIDTH < 0.4)
    return_value += 0.2;
  if (WIDTH < 0.27 || HEIGHT > 0.40)
    return_value += 0.2;
  if (WIDTH_BY_HEIGHT < 0.53)
    return_value += 0.1;
  if (RIGHT_VBAR || MID_VBAR)
    return_value += 0.1;
  if (BOTTOM < 0.58 && BOTTOM > 0.42)
    return_value += 0.1;
  if (TOP_RIGHT > (MID_RIGHT + 0.1))
    return_value += 0.1;
  if (!TOP_MID_CROSS && !TOP_RIGHT_CROSS)
    return_value += 0.1;

  if (TOP_RIGTH_EDGE)
    return_value -= 0.1;
  if (BIG_TOP_RIGTH_EDGE)
    return_value -= 0.1;
  if (LEFT_BOTTOM_EDGE)
    return_value -= 0.1;
  if (BOTTOM_RIGTH_EDGE)
    return_value -= 0.1;
  if (MID_BOTTOM_NOTCH || RIGHT_BOTTOM_NOTCH)
    return_value -= 0.2;
  if (BOTTOM_HBAR)
    return_value -= 0.2;
  if (BOTTOM_HBAR && WIDTH_BY_HEIGHT > 0.35)
    return_value -= 0.2;
  if (BOTTOM > 0.57 || BOTTOM < 47)
    return_value -= 0.1;
  if (BOTTOM < 0.43)
    return_value -= 0.3;
  if (TOP < 0.35)
    return_value -= 0.3;
  if (TOP > 0.65)
    return_value -= 0.3;
  if (WIDTH > 0.25 && (MID_LEFT > (BOTTOM_LEFT + 0.2)))
    return_value -= 0.2;
  if (WIDTH > 0.35)
    return_value -= 0.2;
  if (WIDTH_BY_HEIGHT > 0.53)
    return_value -= 0.1;
  if (WIDTH_BY_HEIGHT > 0.60)
    return_value -= 0.2;
  if (DOT_PART)
    return_value -= 0.2;
  if (!BOTTOM_MID_END && !BOTTOM_RIGHT_END)
    return_value -= 0.2;
  if (HEIGHT < 0.35)
    return_value -= 0.3;
  if (WIDTH_BY_HEIGHT > 0.55)
    return_value -= 0.2;
  if (ONE_HOLE)
    return_value -= 0.2;
  if (DOT_PART)
    return_value -= 0.2;
  if (!RIGHT_VBAR)
    return_value -= 0.2;

  return return_value;
}
