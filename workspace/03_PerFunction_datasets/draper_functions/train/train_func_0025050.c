getNorms(const double * region, int size, double & norm1, double & norm2)
{
     norm1 = 0.0;
     norm2 = 0.0;
     int i;
     for (i = 0; i < size; i++) {
          norm2 += region[i] * region[i];
          norm1 = CoinMax(norm1, fabs(region[i]));
     }
}
