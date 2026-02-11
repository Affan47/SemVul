clamp_freier(entropy, enthalpy)
double entropy, enthalpy;
{
   double tm, top, bot;

   top = 0.0 - 1000.0 * enthalpy;

   bot = 1.987 * (log(Concentration/4.0) + log(0.000000001));
   bot -= entropy;
   if (bot < 0.0)
      tm = top / bot - 273.15;
   else
      tm = 0.0;

   return(tm);
}
