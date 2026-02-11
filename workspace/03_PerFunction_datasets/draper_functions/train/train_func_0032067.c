test_fixed_pitch(void)
{
  int w1, w2;
  int h1, h2;

  w1 = w2 = 0;
  h1 = h2 = 0;

  fl_font((Fl_Font)font, size);

  fl_measure("MHMHWWMHMHMHM###WWX__--HUW", w1, h1, 0);
  fl_measure("iiiiiiiiiiiiiiiiiiiiiiiiii", w2, h2, 0);

  if (w1 == w2) return 1;


  double f1 = (double)w1;
  double f2 = (double)w2;
  double delta = fabs(f1 - f2) * 5.0;
  if (delta <= f1) return 2;

  return 0;
}
