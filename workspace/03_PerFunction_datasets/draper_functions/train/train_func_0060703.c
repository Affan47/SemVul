HTS_Engine_set_beta(HTS_Engine * engine, double f)
{
   if (f < 0.0)
      f = 0.0;
   if (f > 1.0)
      f = 1.0;
   engine->condition.beta = f;
}
