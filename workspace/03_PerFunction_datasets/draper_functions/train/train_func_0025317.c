_pos_map_pow(double pos,
             double divis,
             int    p)
{
   double v = 1.0;
   int i;
   for (i = 0; i < p; i++) v *= pos;
   return ((pos * divis) * (1.0 - v)) + (pos * v);
}
