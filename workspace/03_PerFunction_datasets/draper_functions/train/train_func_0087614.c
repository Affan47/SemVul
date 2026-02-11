ho_recognize_font_1_question (const double *array_in)
{
  double return_value = 0.0;

  if (MID_LEFT_END || TOP_LEFT_END)
    return_value += 0.1;
  if (WIDTH < 0.3)
    return_value += 0.1;
  if (DOT_PART)
    return_value += 0.2;
  if (TOP_RIGTH_EDGE || MID_RIGTH_EDGE)
    return_value += 0.1;

  if (MID_RIGHT_END || TOP_MID_END)
    return_value -= 0.2;
  if (BOTTOM_HBAR)
    return_value -= 0.2;
  if (!DOT_PART)
    return_value -= 0.1;
  if (BOTTOM < 0.45 || BOTTOM > 0.60)
    return_value -= 0.2;
  if (TOP < 0.45 || TOP > 0.58)
    return_value -= 0.2;

  return return_value;
}
