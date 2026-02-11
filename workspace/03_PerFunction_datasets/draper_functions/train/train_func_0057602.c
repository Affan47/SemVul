Cumulative(PRECISION level, int low, int *h, PRECISION min, PRECISION max, int intervals, int sample_size)
{
 PRECISION inc=(max-min)/(PRECISION)intervals;
 int i, count;

 if (level < min) return 0.0;
 if (level >= max) return 1.0;

 for (count=low, i=0; i < intervals; count+=h[i++])
  if ((min+=inc) >= level)
   return ((PRECISION)count + (PRECISION)h[i]*(level - min + inc)/inc)/(PRECISION)sample_size;
 return 1.0;
}
