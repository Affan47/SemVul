missileCount ()
{
  if (id < FIGHTER1 || id > FIGHTER2) return;

  int i;
  for (i = 0; i < missiletypes; i ++)
    missiles [i] = 0;
  for (i = 0; i < missileracks; i ++)
  {
    if (missilerackn [i] > 0)
    {
      missiles [missilerack [i]] += missilerackn [i];
    }
  }
}
