p_calculate_rangesize_pingpong(GapStoryElem *stb_elem)
{
  gdouble fnr;

  if(stb_elem->step_density <= 0)
  {

    stb_elem->step_density = 1.0;
  }

  fnr = 2.0 * (gdouble)(ABS(stb_elem->from_frame - stb_elem->to_frame));
  fnr = fnr / stb_elem->step_density;

  return((gint32)MAX( (fnr+0.5), 1 ));

}
