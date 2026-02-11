p_calc_sector(GapMorphWorkPoint *wp, gdouble dx, gdouble dy)
{
  if(dx >= 0)
  {
    if(dy >= 0)
    {
      if(dx >= dy)
      {
        return(3);
      }
      return(2);
    }
    if(dx >= abs(dy))
    {
      return(4);
    }
    return(5);
  }

  if(dy >= 0)
  {
    if(abs(dx) >= dy)
    {
      return(0);
    }
    return(1);
  }

  if(abs(dx) >= abs(dy))
  {
      return(7);
  }
  return(6);

}
